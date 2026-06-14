#include "boolean.h"
#include "nbtrees.h"
#include <stdio.h>
#include <stdlib.h>

/****************************************************/
/*                MODUL KONSTRUKTOR                  */
/****************************************************/

void Create_tree(Tree *T)
/* I.S. T sembarang */
/* F.S. T menjadi tree kosong */
{
    *T = NULL;
}

address Alokasi(infotype X)
/* Mengalokasikan node baru dengan nilai X */
/* Mengembalikan NULL jika gagal */
{
    address p = (address)malloc(sizeof(Node));
    if (p != NULL)
    {
       
    }
    return p;
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
    printf("%c ", T->info); /* kunjungi node */
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
    printf("%c ", T->info); /* kunjungi node */
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
    printf("%c ", T->info); /* kunjungi node */
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
        printf("%c ", curr->info);

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
    if (T == NULL)
        return;
    for (int i = 0; i < level; i++)
        printf("  ");
    printf("|-- %c\n", T->info);
    PrintTreeRec(T->ps_fs, level + 1); /* cetak anak-anak */
    PrintTreeRec(T->ps_nb, level);     /* cetak saudara pada level yang sama */
}

void PrintTree(Tree T)
/* Menampilkan struktur tree secara visual */
{
    if (IsEmpty(T))
    {
        printf("(Tree kosong)\n");
        return;
    }
    printf("%c\n", T->info);
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

}
void KalkulasiWarisan(address pewaris, float totalHarta){

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
