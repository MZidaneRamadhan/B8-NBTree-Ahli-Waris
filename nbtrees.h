#ifndef nbtrees_h
#define nbtrees_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****************************************************/
/*              DEFINISI TIPE DATA                   */
/****************************************************/
#define true 1
#define false 0

/* Tipe data untuk menyimpan informasi dalam node */
typedef char infotype;

/* Tipe address adalah pointer ke Node */
typedef struct tNode *address;

/* Struktur Node untuk Non-Binary Tree Dinamis */
/* Tipe data khusus untuk menyimpan informasi ahli waris */
typedef struct {
    char Nama[50];
    bool Pasangan;
    bool Gender;     /* true = laki-laki, false = perempuan */
    float Bagian;
    bool Aktif;
    bool Mahjub;
    bool Hidup;      /* true = masih hidup, false = sudah meninggal */
} FaraidhData;

typedef FaraidhData infotype;

/* Tipe address adalah pointer ke Node */
typedef struct tNode *address;

/* Struktur Node memisahkan data (info) dengan pointer tree */
typedef struct tNode {
    infotype info;   /* Wadah penyimpan data ahli waris */
    address ps_fs;   /* pointer ke first son (anak pertama) */
    address ps_nb;   /* pointer ke next brother (saudara berikutnya) */
    address ps_pr;   /* pointer ke parent (induk) */
} Node;

/* Tree direpresentasikan sebagai pointer ke root */
typedef address Tree;

/****************************************************/
/*                MODUL KONSTRUKTOR                  */
/****************************************************/

/* Membuat tree kosong (root = NULL) */
void Create_tree(Tree *T);
/* I.S. T sembarang */
/* F.S. T menjadi tree kosong */

/* Mengalokasikan node baru dengan nilai X */
address Alokasi(infotype X);
/* Mengembalikan address node baru */
/* Jika gagal, mengembalikan NULL */

/****************************************************/
/*                MODUL VALIDASI                     */
/****************************************************/

/* Mengecek apakah tree kosong */
int IsEmpty(Tree T);
/* Mengembalikan 1 jika kosong, 0 jika tidak */

/****************************************************/
/*                MODUL UPDATE                      */
/****************************************************/

/* Menambahkan child sebagai anak dari parent */
void AddChild(address parent, address child);
/* I.S. parent dan child sudah dialokasi */
/* F.S. child menjadi anak dari parent */

/****************************************************/
/*                MODUL TRAVERSAL                   */
/****************************************************/

/* Traversal PreOrder */
/* Mengunjungi: node → anak pertama → saudara */
void PreOrder(Tree T);

/* Traversal InOrder (versi non-binary) */
/* Mengunjungi: anak pertama → node → saudara */
void InOrder(Tree T);

/* Traversal PostOrder */
/* Mengunjungi: anak → saudara → node */
void PostOrder(Tree T);

/* Traversal Level Order (BFS) */
void LevelOrder(Tree T);
/* Menggunakan queue untuk traversal per level */

/* Menampilkan struktur tree */
void PrintTree(Tree T);
/* Menampilkan isi tree secara terstruktur */

/****************************************************/
/*                MODUL STUDI KASUS                   */
/****************************************************/

/* Mencari node dengan nilai X */
address SearchPewaris(Tree T, char namaTarget[]);
/* Mengembalikan address node jika ditemukan, NULL jika tidak */
void AktivasiDanInput(address pewaris);
void CekHijabMahjub(address pewaris);
void KalkulasiWarisan(address pewaris, float totalHarta);

/****************************************************/
/*                MODUL ANALISIS TREE               */
/****************************************************/

/* Menghitung jumlah seluruh node */
int NbElmt(Tree T);

/* Menghitung jumlah daun (node tanpa anak) */
int NbDaun(Tree T);

/* Menghitung level node dengan nilai X */
int Level(Tree T, infotype X);
/* Root berada pada level 1 */

/* Menghitung kedalaman (height) tree */
int Depth(Tree T);

/* Mengembalikan nilai maksimum dari dua bilangan */
int Max(int a, int b);

/****************************************************/
/*                MODUL DEALOKASI                   */
/****************************************************/

/* Menghapus seluruh node dalam tree */
void DeAlokasi(Tree *T);
/* Membebaskan memori tree */

/****************************************************/

#endif