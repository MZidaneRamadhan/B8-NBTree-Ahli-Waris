#include "boolean.h"
#include "nbtrees.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/****************************************************/
/*                MODUL KONSTRUKTOR                  */
/****************************************************/

void Create_tree(Tree *T)
/* I.S. T sembarang */
/* F.S. T menjadi tree kosong */
{
    *T = NULL;
}

infotype MakeInfo(const char *nama, bool gender, bool pasangan)
{
    infotype X;
    strncpy(X.Nama, nama, 49);
    X.Nama[49] = '\0';
    X.Gender = gender;
    X.Pasangan = pasangan;
    X.Bagian = 0.0;
    X.Aktif = false;
    X.Mahjub = false;
    X.Hidup = false;
    return X;
}

address Alokasi(infotype X)
/* Mengalokasikan node baru dengan nilai X */
/* Mengembalikan NULL jika gagal */
{
    address p = (address)malloc(sizeof(Node));
    if (p != NULL)
    {
        strncpy(p->info.Nama, X.Nama, 49);
        p->info.Nama[49] = '\0';
        p->info.Gender = X.Gender;
        p->info.Pasangan = X.Pasangan;
        p->info.Bagian = X.Bagian;
        p->info.Aktif = X.Aktif;
        p->info.Mahjub = false;
        p->info.Hidup = false; /* default: belum diisi */

        p->ps_fs = NULL;
        p->ps_nb = NULL;
        p->ps_pr = NULL;
    }
    return p;
}

address MakeNode(infotype X)
{
    return Alokasi(X);
}

/****************************************************/
/*                MODUL VALIDASI                     */
/****************************************************/

int IsEmpty(Tree T)
/* Mengembalikan 1 jika kosong, 0 jika tidak */
{
    return (T == NULL);
}

/****************************************************/
/*                MODUL UPDATE                      */
/****************************************************/

void AddChild(address parent, address child)
/* I.S. parent dan child sudah dialokasi */
/* F.S. child menjadi anak paling kanan dari parent */
{
    if (parent == NULL || child == NULL)
        return;

    child->ps_pr = parent;

    /* Jika parent belum punya anak, child langsung jadi first son */
    if (parent->ps_fs == NULL)
    {
        parent->ps_fs = child;
    }
    else
    {
        /* Cari saudara paling akhir lalu tempelkan child di sana */
        address curr = parent->ps_fs;
        while (curr->ps_nb != NULL)
        {
            curr = curr->ps_nb;
        }
        curr->ps_nb = child;
    }
}

/****************************************************/
/*                MODUL TRAVERSAL                   */
/****************************************************/

/*
 * PreOrder: node → semua anak (rekursif ke first son) → saudara
 * Urutan: cetak node, lalu PreOrder(fs), lalu PreOrder(nb)
 */
void PreOrder(Tree T)
{
    if (T == NULL)
        return;
    printf("%s | ", T->info.Nama); /* kunjungi node */
    PreOrder(T->ps_fs);     /* kunjungi anak-anak */
    PreOrder(T->ps_nb);     /* kunjungi saudara */
}

/*
 * InOrder (versi non-binary):
 * kunjungi anak pertama → cetak node → sisa saudara
 */
void InOrder(Tree T)
{
    if (T == NULL)
        return;
    InOrder(T->ps_fs);      /* kunjungi anak pertama */
    printf("%s | ", T->info.Nama); /* kunjungi node */
    InOrder(T->ps_nb);      /* kunjungi saudara */
}

/*
 * PostOrder: anak-anak → node → saudara
 */
void PostOrder(Tree T)
{
    if (T == NULL)
        return;
    PostOrder(T->ps_fs);    /* kunjungi anak-anak */
    printf("%s | ", T->info.Nama); /* kunjungi node */
    PostOrder(T->ps_nb);    /* kunjungi saudara */
}

/* ---- Queue sederhana untuk Level Order (BFS) ---- */
#define QUEUE_MAX 256

typedef struct
{
    address data[QUEUE_MAX];
    int front, rear;
} Queue;

static void q_init(Queue *q) { q->front = q->rear = 0; }
static int q_empty(Queue *q) { return q->front == q->rear; }
static void q_push(Queue *q, address a)
{
    if ((q->rear + 1) % QUEUE_MAX == q->front)
        return; /* penuh, abaikan */
    q->data[q->rear] = a;
    q->rear = (q->rear + 1) % QUEUE_MAX;
}
static address q_pop(Queue *q)
{
    address a = q->data[q->front];
    q->front = (q->front + 1) % QUEUE_MAX;
    return a;
}

void LevelOrder(Tree T)
/* Traversal BFS: cetak node level demi level */
{
    if (T == NULL)
        return;

    Queue q;
    q_init(&q);
    q_push(&q, T);

    while (!q_empty(&q))
    {
        address curr = q_pop(&q);
        printf("%s | ", curr->info.Nama);

        /* Masukkan semua anak ke queue */
        address child = curr->ps_fs;
        while (child != NULL)
        {
            q_push(&q, child);
            child = child->ps_nb;
        }
    }
}

/* ---- PrintTree helper ---- */
static void PrintTreeRec(Tree T, int level)
{
    if (T == NULL) return;

    for (int i = 0; i < level; i++)
        printf("  ");
    printf("|-- %s\n", T->info.Nama);   /* ganti %c → %s, T->info → T->info.Nama */

    PrintTreeRec(T->ps_fs, level + 1);
    PrintTreeRec(T->ps_nb, level);
}

void PrintTree(Tree T)
{
    if (IsEmpty(T))
    {
        printf("(Tree kosong)\n");
        return;
    }
    printf("%s\n", T->info.Nama);       /* ganti %c → %s, T->info → T->info.Nama */
    PrintTreeRec(T->ps_fs, 1);
}

/****************************************************/
/*                MODUL STUDI KASUS                   */
/****************************************************/
address SearchPewaris(Tree T, const char* namaTarget) {
    if (T == NULL) return NULL;
    if (strcmp(T->info.Nama, namaTarget) == 0) return T;

    address found = SearchPewaris(T->ps_fs, namaTarget);
    if (found != NULL) return found;
    
    return SearchPewaris(T->ps_nb, namaTarget);
}

static void TanyaStatus(address node) {
    if (node == NULL) return;
    int inputStatus;
    printf("Apakah %s masih hidup? (1 = hidup, 0 = wafat): ", node->info.Nama);
    if (scanf("%d", &inputStatus) == 1) {
        node->info.Hidup = (inputStatus == 1);
        node->info.Aktif = true; 
    } else {
        printf("Input tidak valid. Default ke wafat.\n");
        node->info.Hidup = false;
        node->info.Aktif = false;
    }
}

void AktivasiDanInput(address pewaris) {
    if (pewaris == NULL) return;

    pewaris->info.Hidup = false;
    pewaris->info.Aktif = true; 

    /* (Ayah & Kakek) */
    if (pewaris->ps_pr != NULL) {
        address ayah = pewaris->ps_pr;
        TanyaStatus(ayah);
        if (ayah->ps_pr != NULL) {
            address kakek = ayah->ps_pr;
            TanyaStatus(kakek);
        }
    }

    /* (Anak & Cucu) */
    address anak = pewaris->ps_fs;
    while (anak != NULL) {
        TanyaStatus(anak);
        address cucu = anak->ps_fs;
        while (cucu != NULL) {
            TanyaStatus(cucu);
            cucu = cucu->ps_nb; 
        }
        anak = anak->ps_nb; 
    }

    /* (Saudara Kandung) */
    if (pewaris->ps_pr != NULL) {
        address saudara = pewaris->ps_pr->ps_fs;
        while (saudara != NULL) {
            if (saudara != pewaris) TanyaStatus(saudara);
            saudara = saudara->ps_nb; 
        }
    }

    /* Pasangan */
    if (pewaris->info.Pasangan == true) {
        int statusPasangan;
        printf("Apakah pasangan %s masih hidup? (1/0): ", pewaris->info.Nama);
        if (scanf("%d", &statusPasangan) == 1) {
        }
    }
}
void CekHijabMahjub(address pewaris){
    if (pewaris == NULL)
        return;

    printf("\n=== CEK HIJAB & MAHJUB ===\n");

    /* --- Kumpulkan status relevan --- */
    bool adaAnakLaki = false;
    bool adaAyah = false;
    bool adaCucuLaki = false;

    /* Cek anak laki-laki */
    address anak = pewaris->ps_fs;
    while (anak != NULL)
    {
        if (anak->info.Aktif && anak->info.Hidup && anak->info.Gender == true)
        {
            adaAnakLaki = true;
        }
        /* Cek cucu laki-laki */
        address cucu = anak->ps_fs;
        while (cucu != NULL)
        {
            if (cucu->info.Aktif && cucu->info.Hidup && cucu->info.Gender == true)
                adaCucuLaki = true;
            cucu = cucu->ps_nb;
        }
        anak = anak->ps_nb;
    }

    /* Cek ayah */
    if (pewaris->ps_pr != NULL)
    {
        address ayah = pewaris->ps_pr;
        if (ayah->info.Aktif && ayah->info.Hidup)
            adaAyah = true;
    }

    /* --- Terapkan aturan hijab --- */

    /* Aturan a & b: jika ada anak laki-laki ATAU ayah → saudara kandung mahjub */
    if (adaAnakLaki || adaCucuLaki || adaAyah)
    {
        if (pewaris->ps_pr != NULL)
        {
            address saudara = pewaris->ps_pr->ps_fs;
            while (saudara != NULL)
            {
                if (saudara != pewaris && saudara->info.Aktif && saudara->info.Hidup)
                {
                    saudara->info.Mahjub = true;
                    printf("  [MAHJUB] %-25s dihijab oleh %s\n",
                           saudara->info.Nama,
                           adaAnakLaki ? "Anak Laki-laki" : adaCucuLaki ? "Cucu Laki-laki"
                                                                        : "Ayah");
                }
                saudara = saudara->ps_nb;
            }
        }
    }

    /* Aturan b: jika ada ayah → kakek mahjub */
    if (adaAyah && pewaris->ps_pr != NULL && pewaris->ps_pr->ps_pr != NULL)
    {
        address kakek = pewaris->ps_pr->ps_pr;
        if (kakek->info.Aktif && kakek->info.Hidup)
        {
            kakek->info.Mahjub = true;
            printf("  [MAHJUB] %-25s dihijab oleh Ayah\n", kakek->info.Nama);
        }
    }

    /* Aturan a: jika ada anak laki-laki → cucu mahjub */
    if (adaAnakLaki)
    {
        anak = pewaris->ps_fs;
        while (anak != NULL)
        {
            address cucu = anak->ps_fs;
            while (cucu != NULL)
            {
                if (cucu->info.Aktif && cucu->info.Hidup)
                {
                    cucu->info.Mahjub = true;
                    printf("  [MAHJUB] %-25s dihijab oleh Anak Laki-laki\n",
                           cucu->info.Nama);
                }
                cucu = cucu->ps_nb;
            }
            anak = anak->ps_nb;
        }
    }

    printf("  Pengecekan selesai.\n");
}
void KalkulasiWarisan(address pewaris, float totalHarta){
    if (pewaris == NULL || totalHarta <= 0)
        return;

    printf("\n=== KALKULASI PEMBAGIAN WARISAN ===\n");
    printf("Total Harta : Rp %.2f\n\n", totalHarta);

    float sisa = totalHarta;

    /* ================================================================
     * TAHAP 1: Kumpulkan status ahli waris yang relevan
     * ================================================================ */

    /* --- Anak langsung pewaris --- */
    int jmlAnakLaki = 0, jmlAnakPr = 0;
    address anak = pewaris->ps_fs;
    while (anak != NULL)
    {
        if (anak->info.Aktif && anak->info.Hidup && !anak->info.Mahjub)
        {
            if (anak->info.Gender)
                jmlAnakLaki++;
            else
                jmlAnakPr++;
        }
        anak = anak->ps_nb;
    }
    bool adaAnakLaki = jmlAnakLaki > 0;
    bool adaAnakPr = jmlAnakPr > 0;
    bool adaAnak = adaAnakLaki || adaAnakPr;

    /* --- Cucu laki-laki dari anak laki-laki --- */
    int jmlCucuLaki = 0, jmlCucuPr = 0;
    anak = pewaris->ps_fs;
    while (anak != NULL)
    {
        if (anak->info.Aktif && anak->info.Hidup && !anak->info.Mahjub && anak->info.Gender)
        {
            /* Hanya cucu dari anak laki-laki yang dihitung */
            address cucu = anak->ps_fs;
            while (cucu != NULL)
            {
                if (cucu->info.Aktif && cucu->info.Hidup && !cucu->info.Mahjub)
                {
                    if (cucu->info.Gender)
                        jmlCucuLaki++;
                    else
                        jmlCucuPr++;
                }
                cucu = cucu->ps_nb;
            }
        }
        anak = anak->ps_nb;
    }
    bool adaCucuLaki = jmlCucuLaki > 0;
    bool adaCucuPr = jmlCucuPr > 0;

    /* --- Keturunan (anak atau cucu) --- */
    bool adaKeturunan = adaAnak || adaCucuLaki || adaCucuPr;

    /* --- Ayah --- */
    address ayah = NULL;
    bool adaAyah = false;
    if (pewaris->ps_pr != NULL)
    {
        ayah = pewaris->ps_pr;
        if (ayah->info.Aktif && ayah->info.Hidup && !ayah->info.Mahjub)
            adaAyah = true;
    }

    /* --- Kakek shahih (ayah dari ayah) --- */
    address kakek = NULL;
    bool adaKakek = false;
    if (ayah != NULL && ayah->ps_pr != NULL)
    {
        kakek = ayah->ps_pr;
        if (!adaAyah && kakek->info.Aktif && kakek->info.Hidup && !kakek->info.Mahjub)
            adaKakek = true;
    }

    /* --- Saudara kandung (anak dari ayah yang bukan pewaris) --- */
    int jmlSaudaraLaki = 0, jmlSaudaraPr = 0;
    if (adaAyah && ayah != NULL)
    {
        address sdr = ayah->ps_fs;
        while (sdr != NULL)
        {
            if (sdr != pewaris && sdr->info.Aktif &&
                sdr->info.Hidup && !sdr->info.Mahjub)
            {
                if (sdr->info.Gender)
                    jmlSaudaraLaki++;
                else
                    jmlSaudaraPr++;
            }
            sdr = sdr->ps_nb;
        }
    }
    bool adaSaudaraLaki = jmlSaudaraLaki > 0;
    bool adaSaudaraPr = jmlSaudaraPr > 0;
    int totalSaudara = jmlSaudaraLaki + jmlSaudaraPr;

    /* ================================================================
     * TAHAP 2: Ashhabul Furudh (penerima bagian tetap)
     * ================================================================ */
    printf("  [Ashhabul Furudh]\n");

    /* ----------------------------------------------------------
     * PASANGAN
     * Suami : 1/2 jika tidak ada keturunan, 1/4 jika ada
     * Istri  : 1/4 jika tidak ada keturunan, 1/8 jika ada
     * ---------------------------------------------------------- */
    if (pewaris->info.Pasangan)
    {
        float bagian;
        const char *label;
        if (pewaris->info.Gender)
        {
            /* Pewaris laki-laki → pasangannya istri */
            bagian = adaKeturunan ? totalHarta / 8.0f : totalHarta / 4.0f;
            label = "Istri";
        }
        else
        {
            /* Pewaris perempuan → pasangannya suami */
            bagian = adaKeturunan ? totalHarta / 4.0f : totalHarta / 2.0f;
            label = "Suami";
        }
        printf("  %-30s : Rp %12.2f  (%.2f%%)\n",
               label, bagian, (bagian / totalHarta) * 100.0f);
        sisa -= bagian;
    }

    /* ----------------------------------------------------------
     * AYAH
     * - Ada anak laki-laki           → 1/6
     * - Ada anak pr saja (tanpa laki)→ 1/6 + sisa (ashabah)
     * - Tidak ada anak sama sekali   → ashabah (ditangani Tahap 3)
     * ---------------------------------------------------------- */
    float bagianAyahFurudh = 0.0f;
    bool ayahAshabah = false;
    if (adaAyah)
    {
        if (adaAnakLaki)
        {
            /* Kasus 1: ada anak laki-laki → ayah hanya 1/6 */
            bagianAyahFurudh = totalHarta / 6.0f;
            printf("  %-30s : Rp %12.2f  (%.2f%%) [1/6]\n",
                   ayah->info.Nama, bagianAyahFurudh,
                   (bagianAyahFurudh / totalHarta) * 100.0f);
            ayah->info.Bagian = bagianAyahFurudh;
            sisa -= bagianAyahFurudh;
        }
        else if (adaAnakPr && !adaAnakLaki)
        {
            /* Kasus 2: ada anak pr saja → ayah 1/6 furudh + ashabah di Tahap 3 */
            bagianAyahFurudh = totalHarta / 6.0f;
            printf("  %-30s : Rp %12.2f  (%.2f%%) [1/6 + sisa ashabah]\n",
                   ayah->info.Nama, bagianAyahFurudh,
                   (bagianAyahFurudh / totalHarta) * 100.0f);
            ayah->info.Bagian = bagianAyahFurudh;
            sisa -= bagianAyahFurudh;
            ayahAshabah = true; /* sisa akan ditambahkan di Tahap 3 */
        }
        else
        {
            /* Kasus 3: tidak ada anak → ayah ashabah murni */
            ayahAshabah = true;
            printf("  %-30s : [Ashabah — dihitung setelah furudh]\n",
                   ayah->info.Nama);
        }
    }

    /* ----------------------------------------------------------
     * KAKEK SHAHIH (hanya jika ayah tidak ada)
     * Aturan sama dengan ayah
     * ---------------------------------------------------------- */
    float bagianKakekFurudh = 0.0f;
    bool kakekAshabah = false;
    if (adaKakek)
    {
        if (adaAnakLaki)
        {
            bagianKakekFurudh = totalHarta / 6.0f;
            printf("  %-30s : Rp %12.2f  (%.2f%%) [1/6]\n",
                   kakek->info.Nama, bagianKakekFurudh,
                   (bagianKakekFurudh / totalHarta) * 100.0f);
            kakek->info.Bagian = bagianKakekFurudh;
            sisa -= bagianKakekFurudh;
        }
        else if (adaAnakPr && !adaAnakLaki)
        {
            bagianKakekFurudh = totalHarta / 6.0f;
            printf("  %-30s : Rp %12.2f  (%.2f%%) [1/6 + sisa ashabah]\n",
                   kakek->info.Nama, bagianKakekFurudh,
                   (bagianKakekFurudh / totalHarta) * 100.0f);
            kakek->info.Bagian = bagianKakekFurudh;
            sisa -= bagianKakekFurudh;
            kakekAshabah = true;
        }
        else
        {
            kakekAshabah = true;
            printf("  %-30s : [Ashabah — dihitung setelah furudh]\n",
                   kakek->info.Nama);
        }
    }

    /* ----------------------------------------------------------
     * ANAK PEREMPUAN (furudh, hanya jika tidak ada anak laki-laki)
     * - 1 anak pr          → 1/2
     * - ≥2 anak pr         → 2/3 dibagi rata
     * - Ada anak laki-laki → ashabah bil ghair (Tahap 3)
     * ---------------------------------------------------------- */
    if (adaAnakPr && !adaAnakLaki)
    {
        float totalBagianPr = (jmlAnakPr == 1)
                                  ? totalHarta / 2.0f
                                  : totalHarta * 2.0f / 3.0f;
        float perOrang = totalBagianPr / (float)jmlAnakPr;
        const char *keterangan = (jmlAnakPr == 1) ? "1/2" : "2/3 dibagi rata";

        anak = pewaris->ps_fs;
        while (anak != NULL)
        {
            if (anak->info.Aktif && anak->info.Hidup &&
                !anak->info.Mahjub && !anak->info.Gender)
            {
                printf("  %-30s : Rp %12.2f  (%.2f%%) [%s]\n",
                       anak->info.Nama, perOrang,
                       (perOrang / totalHarta) * 100.0f, keterangan);
                anak->info.Bagian = perOrang;
                sisa -= perOrang;
            }
            anak = anak->ps_nb;
        }
    }

    /* ----------------------------------------------------------
     * CUCU PEREMPUAN dari anak laki-laki (furudh)
     * Hanya jika tidak ada anak perempuan dan tidak ada anak laki-laki
     * - 1 cucu pr   → 1/2
     * - ≥2 cucu pr  → 2/3
     * - 1 anak pr + cucu pr → cucu pr dapat 1/6 (pelengkap 2/3)
     * ---------------------------------------------------------- */
    if (adaCucuPr && !adaAnakLaki && !adaCucuLaki)
    {
        float totalBagianCucuPr;
        const char *ketCucu;

        if (!adaAnakPr)
        {
            /* Tidak ada anak pr sama sekali */
            totalBagianCucuPr = (jmlCucuPr == 1)
                                    ? totalHarta / 2.0f
                                    : totalHarta * 2.0f / 3.0f;
            ketCucu = (jmlCucuPr == 1) ? "1/2" : "2/3 dibagi rata";
        }
        else if (jmlAnakPr == 1)
        {
            /* Ada 1 anak pr → cucu pr dapat 1/6 sebagai pelengkap 2/3 */
            totalBagianCucuPr = totalHarta / 6.0f;
            ketCucu = "1/6 pelengkap 2/3";
        }
        else
        {
            /* Anak pr sudah ≥2 → cucu pr terhalang (mahjub) */
            totalBagianCucuPr = 0.0f;
            ketCucu = "terhalang anak perempuan ≥2";
        }

        if (totalBagianCucuPr > 0)
        {
            float perOrang = totalBagianCucuPr / (float)jmlCucuPr;
            anak = pewaris->ps_fs;
            while (anak != NULL)
            {
                if (anak->info.Aktif && anak->info.Hidup &&
                    !anak->info.Mahjub && anak->info.Gender)
                {
                    address cucu = anak->ps_fs;
                    while (cucu != NULL)
                    {
                        if (cucu->info.Aktif && cucu->info.Hidup &&
                            !cucu->info.Mahjub && !cucu->info.Gender)
                        {
                            printf("  %-30s : Rp %12.2f  (%.2f%%) [%s]\n",
                                   cucu->info.Nama, perOrang,
                                   (perOrang / totalHarta) * 100.0f, ketCucu);
                            cucu->info.Bagian = perOrang;
                            sisa -= perOrang;
                        }
                        cucu = cucu->ps_nb;
                    }
                }
                anak = anak->ps_nb;
            }
        }
    }

    /* ----------------------------------------------------------
     * SAUDARI KANDUNG (furudh, hanya jika tidak ada anak & ayah)
     * - 1 saudari  → 1/2
     * - ≥2 saudari → 2/3
     * - Bersama anak pr → ashabah ma'al ghair (Tahap 3)
     * ---------------------------------------------------------- */
    bool saudariAshabahMaal = false;
    if (!adaKeturunan && !adaAyah && !adaKakek && adaSaudaraPr)
    {
        if (adaAnakPr || adaCucuPr)
        {
            /* Ashabah ma'al ghair — ditangani Tahap 3 */
            saudariAshabahMaal = true;
            if (ayah != NULL)
            {
                address sdr = ayah->ps_fs;
                while (sdr != NULL)
                {
                    if (sdr != pewaris && sdr->info.Aktif &&
                        sdr->info.Hidup && !sdr->info.Mahjub && !sdr->info.Gender)
                    {
                        printf("  %-30s : [Ashabah ma'al ghair]\n", sdr->info.Nama);
                    }
                    sdr = sdr->ps_nb;
                }
            }
        }
        else
        {
            float totalBagianSdrPr = (jmlSaudaraPr == 1)
                                         ? totalHarta / 2.0f
                                         : totalHarta * 2.0f / 3.0f;
            float perOrang = totalBagianSdrPr / (float)jmlSaudaraPr;
            const char *ketSdr = (jmlSaudaraPr == 1) ? "1/2" : "2/3 dibagi rata";

            if (ayah != NULL)
            {
                address sdr = ayah->ps_fs;
                while (sdr != NULL)
                {
                    if (sdr != pewaris && sdr->info.Aktif &&
                        sdr->info.Hidup && !sdr->info.Mahjub && !sdr->info.Gender)
                    {
                        printf("  %-30s : Rp %12.2f  (%.2f%%) [%s]\n",
                               sdr->info.Nama, perOrang,
                               (perOrang / totalHarta) * 100.0f, ketSdr);
                        sdr->info.Bagian = perOrang;
                        sisa -= perOrang;
                    }
                    sdr = sdr->ps_nb;
                }
            }
        }
    }

    /* ================================================================
     * TAHAP 3: Ashabah (penerima sisa harta)
     * Prioritas: anak laki-laki → cucu laki-laki → ayah → kakek
     *            → saudara laki-laki → saudari (ashabah ma'al ghair)
     * ================================================================ */
    printf("\n  [Ashabah --- Sisa: Rp %.2f]\n", sisa > 0 ? sisa : 0.0f);

    if (sisa > 0.0f)
    {

        /* -- Anak laki-laki + anak perempuan (ashabah bil ghair) -- */
        if (adaAnakLaki)
        {
            /*
             * Pembagian: laki-laki mendapat 2x bagian perempuan
             * Unit total = jmlAnakLaki*2 + jmlAnakPr
             */
            int totalUnit = jmlAnakLaki * 2 + jmlAnakPr;
            float perUnit = sisa / (float)totalUnit;

            anak = pewaris->ps_fs;
            while (anak != NULL)
            {
                if (anak->info.Aktif && anak->info.Hidup && !anak->info.Mahjub)
                {
                    float bagian = anak->info.Gender ? perUnit * 2.0f : perUnit;
                    printf("  %-30s : Rp %12.2f  (%.2f%%) [ashabah bil ghair]\n",
                           anak->info.Nama, bagian,
                           (bagian / totalHarta) * 100.0f);
                    anak->info.Bagian += bagian;
                }
                anak = anak->ps_nb;
            }
            sisa = 0.0f;
        }

        /* -- Cucu laki-laki (jika tidak ada anak laki-laki) -- */
        else if (adaCucuLaki && !adaAnakLaki)
        {
            int totalUnit = jmlCucuLaki * 2 + jmlCucuPr;
            float perUnit = sisa / (float)totalUnit;

            anak = pewaris->ps_fs;
            while (anak != NULL)
            {
                if (anak->info.Aktif && anak->info.Hidup &&
                    !anak->info.Mahjub && anak->info.Gender)
                {
                    address cucu = anak->ps_fs;
                    while (cucu != NULL)
                    {
                        if (cucu->info.Aktif && cucu->info.Hidup && !cucu->info.Mahjub)
                        {
                            float bagian = cucu->info.Gender ? perUnit * 2.0f : perUnit;
                            printf("  %-30s : Rp %12.2f  (%.2f%%) [ashabah]\n",
                                   cucu->info.Nama, bagian,
                                   (bagian / totalHarta) * 100.0f);
                            cucu->info.Bagian += bagian;
                        }
                        cucu = cucu->ps_nb;
                    }
                }
                anak = anak->ps_nb;
            }
            sisa = 0.0f;
        }

        /* -- Ayah ashabah (tidak ada anak sama sekali, atau ada anak pr) -- */
        else if (ayahAshabah && adaAyah)
        {
            printf("  %-30s : Rp %12.2f  (%.2f%%) [ashabah]\n",
                   ayah->info.Nama, sisa,
                   (sisa / totalHarta) * 100.0f);
            ayah->info.Bagian += sisa;
            sisa = 0.0f;
        }

        /* -- Kakek ashabah (tidak ada anak & tidak ada ayah) -- */
        else if (kakekAshabah && adaKakek)
        {
            printf("  %-30s : Rp %12.2f  (%.2f%%) [ashabah]\n",
                   kakek->info.Nama, sisa,
                   (sisa / totalHarta) * 100.0f);
            kakek->info.Bagian += sisa;
            sisa = 0.0f;
        }

        /* -- Saudara laki-laki kandung (ashabah) -- */
        else if (adaSaudaraLaki && !adaKeturunan && !adaAyah && !adaKakek)
        {
            int totalUnit = jmlSaudaraLaki * 2 + (saudariAshabahMaal ? jmlSaudaraPr : 0);
            float perUnit = sisa / (float)totalUnit;

            if (ayah != NULL)
            {
                address sdr = ayah->ps_fs;
                while (sdr != NULL)
                {
                    if (sdr != pewaris && sdr->info.Aktif &&
                        sdr->info.Hidup && !sdr->info.Mahjub)
                    {
                        bool ikutAshabah = sdr->info.Gender ||
                                           (saudariAshabahMaal && !sdr->info.Gender);
                        if (ikutAshabah)
                        {
                            float bagian = sdr->info.Gender
                                               ? perUnit * 2.0f
                                               : perUnit;
                            printf("  %-30s : Rp %12.2f  (%.2f%%) [ashabah]\n",
                                   sdr->info.Nama, bagian,
                                   (bagian / totalHarta) * 100.0f);
                            sdr->info.Bagian += bagian;
                        }
                    }
                    sdr = sdr->ps_nb;
                }
            }
            sisa = 0.0f;
        }

        /* -- Saudari kandung ashabah ma'al ghair (tanpa saudara laki) -- */
        else if (saudariAshabahMaal && !adaSaudaraLaki)
        {
            float perOrang = sisa / (float)jmlSaudaraPr;
            if (ayah != NULL)
            {
                address sdr = ayah->ps_fs;
                while (sdr != NULL)
                {
                    if (sdr != pewaris && sdr->info.Aktif &&
                        sdr->info.Hidup && !sdr->info.Mahjub && !sdr->info.Gender)
                    {
                        printf("  %-30s : Rp %12.2f  (%.2f%%) [ashabah ma'al ghair]\n",
                               sdr->info.Nama, perOrang,
                               (perOrang / totalHarta) * 100.0f);
                        sdr->info.Bagian += perOrang;
                    }
                    sdr = sdr->ps_nb;
                }
            }
            sisa = 0.0f;
        }
    }

    /* ================================================================
     * RINGKASAN AKHIR
     * ================================================================ */
    printf("\n------------------------------------------\n");
    printf("  Sisa (Rad/Baitul Mal) : Rp %.2f\n", sisa < 0.0f ? 0.0f : sisa);
    printf("==========================================\n");
}


/****************************************************/
/*                MODUL ANALISIS TREE               */
/****************************************************/

int NbElmt(Tree T)
/* Menghitung jumlah seluruh node */
{
    if (T == NULL)
        return 0;
    return 1 + NbElmt(T->ps_fs) + NbElmt(T->ps_nb);
}

int NbDaun(Tree T)
/* Menghitung jumlah daun (node tanpa anak) */
{
    if (T == NULL)
        return 0;
    if (T->ps_fs == NULL) /* node ini adalah daun */
        return 1 + NbDaun(T->ps_nb);
    return NbDaun(T->ps_fs) + NbDaun(T->ps_nb);
}

int Max(int a, int b)
{
    return (a > b) ? a : b;
}

/*
 * Level: mengembalikan level node bernilai X
 * Root berada di level 1.
 * Mengembalikan -1 jika tidak ditemukan.
 */
int Level(Tree T, infotype X)
{
    if (T == NULL)
        return -1;
    if (strcmp(T->info.Nama, X.Nama) == 0)
        return 1;

    /* Cari di anak-anak (level bertambah 1) */
    int lvl = Level(T->ps_fs, X);
    if (lvl != -1)
        return lvl + 1;

    /* Cari di saudara (level tidak berubah) */
    return Level(T->ps_nb, X);
}

/*
 * Depth: kedalaman (tinggi) tree.
 * Tree dengan satu node memiliki depth 1.
 */
int Depth(Tree T)
{
    if (T == NULL)
        return 0;

    int depthChild = Depth(T->ps_fs);   /* kedalaman melalui anak */
    int depthSibling = Depth(T->ps_nb); /* kedalaman melalui saudara */

    /* Kedalaman melalui anak bertambah 1 dari node ini */
    return Max(depthChild + 1, depthSibling);
}

/****************************************************/
/*                MODUL DEALOKASI                   */
/****************************************************/

void DeAlokasi(Tree *T)
/* Membebaskan seluruh memori tree secara post-order */
{
    if (*T == NULL)
        return;
    DeAlokasi(&((*T)->ps_fs)); /* bebaskan anak-anak */
    DeAlokasi(&((*T)->ps_nb)); /* bebaskan saudara */
    free(*T);
    *T = NULL;
}
