#include <stdio.h>
#include "nbtrees.h"

Tree BangunSilsilah(void)
{
    /* ================================================================
     * GENERASI 0: ROOT
     * ================================================================ */
    address abdulMuthalib = MakeNode(MakeInfo("Abdul Muthalib", true, true));

    /* ================================================================
     * GENERASI 1: Putra-putri Abdul Muthalib
     * ================================================================ */
    address abdullah = MakeNode(MakeInfo("Abdullah", true, true));
    address abuThalib = MakeNode(MakeInfo("Abu Thalib", true, true));
    address alAbbas = MakeNode(MakeInfo("Al-Abbas", true, true));
    address hamzah = MakeNode(MakeInfo("Hamzah", true, true));
    address alHarits = MakeNode(MakeInfo("Al-Harits", true, true));
    address abuLahab = MakeNode(MakeInfo("Abu Lahab", true, true));
    address azZubair = MakeNode(MakeInfo("Az-Zubair", true, true));
    address shafiyyah = MakeNode(MakeInfo("Shafiyyah", false, true));
    address ummuHakim = MakeNode(MakeInfo("Ummu Hakim Al-Baidha", false, true));

    /* ================================================================
     * GENERASI 2: Anak dari masing-masing G1
     * ================================================================ */

    /* -- Anak Abdullah -- */
    address nabi = MakeNode(MakeInfo("Muhammad SAW", true, true));

    /* -- Anak Abu Thalib -- */
    address thalib = MakeNode(MakeInfo("Thalib", true, false));
    address aqil = MakeNode(MakeInfo("Aqil", true, false));
    address jafar = MakeNode(MakeInfo("Ja'far", true, true));
    address aliBinAbiThalib = MakeNode(MakeInfo("Ali bin Abi Thalib", true, true));

    /* -- Anak Al-Abbas -- */
    address alFadhl = MakeNode(MakeInfo("Al-Fadhl", true, false));
    address abdullahBinAbbas = MakeNode(MakeInfo("Abdullah bin Abbas", true, false));
    address qutsam = MakeNode(MakeInfo("Qutsam", true, false));
    address maabad = MakeNode(MakeInfo("Ma'bad", true, false));

    /* -- Anak Hamzah -- */
    address umamahBintiHamzah = MakeNode(MakeInfo("Umamah binti Hamzah", false, false));

    /* -- Anak Al-Harits -- */
    address abuSufyanBinHarits = MakeNode(MakeInfo("Abu Sufyan bin Al-Harits", true, false));
    address rabiahBinHarits = MakeNode(MakeInfo("Rabi'ah bin Al-Harits", true, false));
    address nawfal = MakeNode(MakeInfo("Nawfal", true, false));

    /* -- Anak Abu Lahab -- */
    address utbah = MakeNode(MakeInfo("Utbah", true, false));
    address utaibah = MakeNode(MakeInfo("Utaibah", true, false));
    address muattab = MakeNode(MakeInfo("Muattab", true, false));

    /* -- Anak Az-Zubair bin Abdul Muthalib -- */
    address abdullahBinAzZubair = MakeNode(MakeInfo("Abdullah bin Az-Zubair", true, false));

    /* -- Anak Shafiyyah -- */
    address zubairBinAwwam = MakeNode(MakeInfo("Zubair bin Awwam", true, true));

    /* -- Anak Ummu Hakim Al-Baidha -- */
    address arwaBintiKurayz = MakeNode(MakeInfo("Arwa binti Kurayz", false, true));

    /* ================================================================
     * GENERASI 3: Anak dari masing-masing G2
     * ================================================================ */

    /* -- Anak Muhammad SAW -- */
    address alQasim = MakeNode(MakeInfo("Al-Qasim", true, false));
    address abdullahBinNabi = MakeNode(MakeInfo("Abdullah bin Muhammad", true, false));
    address ibrahim = MakeNode(MakeInfo("Ibrahim", true, false));
    address zainabBintiNabi = MakeNode(MakeInfo("Zainab binti Muhammad", false, true));
    address ruqayyah = MakeNode(MakeInfo("Ruqayyah", false, false));
    address ummuKultsum = MakeNode(MakeInfo("Ummu Kultsum", false, false));
    address fatimah = MakeNode(MakeInfo("Fatimah Az-Zahra", false, true));

    /* -- Anak Ja'far bin Abu Thalib -- */
    address abdullahBinJafar = MakeNode(MakeInfo("Abdullah bin Ja'far", true, false));
    address muhammadBinJafar = MakeNode(MakeInfo("Muhammad bin Ja'far", true, false));
    address aunBinJafar = MakeNode(MakeInfo("Aun bin Ja'far", true, false));

    /* -- Anak Ali bin Abi Thalib -- */
    address hasanBinAli = MakeNode(MakeInfo("Hasan bin Ali", true, false));
    address husainBinAli = MakeNode(MakeInfo("Husain bin Ali", true, false));
    address zainabBintiAli = MakeNode(MakeInfo("Zainab binti Ali", false, false));
    address ummuKultsumAli = MakeNode(MakeInfo("Ummu Kultsum binti Ali", false, false));

    /* -- Anak Abdullah bin Abbas -- */
    address aliBinAbdullah = MakeNode(MakeInfo("Ali bin Abdullah", true, false));

    /* -- Anak Abu Sufyan bin Al-Harits -- */
    address jafarBinAbuSufyan = MakeNode(MakeInfo("Ja'far bin Abu Sufyan", true, false));

    /* -- Anak Zubair bin Awwam (cucu Shafiyyah) -- */
    address abdullahBinZubair = MakeNode(MakeInfo("Abdullah bin Zubair", true, false));
    address musabBinZubair = MakeNode(MakeInfo("Mush'ab bin Zubair", true, false));
    address urwahBinZubair = MakeNode(MakeInfo("Urwah bin Zubair", true, false));

    /* -- Anak Arwa binti Kurayz (cucu Ummu Hakim) -- */
    address utsmanBinAffan = MakeNode(MakeInfo("Utsman bin Affan", true, true));
    address amnaBintiAffan = MakeNode(MakeInfo("Amna binti Affan", false, false));

    /* ================================================================
     * GENERASI 4: Anak Fatimah Az-Zahra
     * ================================================================ */
    address hasan = MakeNode(MakeInfo("Hasan", true, false));
    address husain = MakeNode(MakeInfo("Husain", true, false));

    /* ================================================================
     * SUSUN RELASI PARENT → CHILD
     * ================================================================ */

    /* ROOT → G1 */
    AddChild(abdulMuthalib, abdullah);
    AddChild(abdulMuthalib, abuThalib);
    AddChild(abdulMuthalib, alAbbas);
    AddChild(abdulMuthalib, hamzah);
    AddChild(abdulMuthalib, alHarits);
    AddChild(abdulMuthalib, abuLahab);
    AddChild(abdulMuthalib, azZubair);
    AddChild(abdulMuthalib, shafiyyah);
    AddChild(abdulMuthalib, ummuHakim);

    /* G1 → G2 */
    AddChild(abdullah, nabi);

    AddChild(abuThalib, thalib);
    AddChild(abuThalib, aqil);
    AddChild(abuThalib, jafar);
    AddChild(abuThalib, aliBinAbiThalib);

    AddChild(alAbbas, alFadhl);
    AddChild(alAbbas, abdullahBinAbbas);
    AddChild(alAbbas, qutsam);
    AddChild(alAbbas, maabad);

    AddChild(hamzah, umamahBintiHamzah);

    AddChild(alHarits, abuSufyanBinHarits);
    AddChild(alHarits, rabiahBinHarits);
    AddChild(alHarits, nawfal);

    AddChild(abuLahab, utbah);
    AddChild(abuLahab, utaibah);
    AddChild(abuLahab, muattab);

    AddChild(azZubair, abdullahBinAzZubair);

    AddChild(shafiyyah, zubairBinAwwam);

    AddChild(ummuHakim, arwaBintiKurayz);

    /* G2 → G3 */
    AddChild(nabi, alQasim);
    AddChild(nabi, abdullahBinNabi);
    AddChild(nabi, ibrahim);
    AddChild(nabi, zainabBintiNabi);
    AddChild(nabi, ruqayyah);
    AddChild(nabi, ummuKultsum);
    AddChild(nabi, fatimah);

    AddChild(jafar, abdullahBinJafar);
    AddChild(jafar, muhammadBinJafar);
    AddChild(jafar, aunBinJafar);

    AddChild(aliBinAbiThalib, hasanBinAli);
    AddChild(aliBinAbiThalib, husainBinAli);
    AddChild(aliBinAbiThalib, zainabBintiAli);
    AddChild(aliBinAbiThalib, ummuKultsumAli);

    AddChild(abdullahBinAbbas, aliBinAbdullah);

    AddChild(abuSufyanBinHarits, jafarBinAbuSufyan);

    AddChild(zubairBinAwwam, abdullahBinZubair);
    AddChild(zubairBinAwwam, musabBinZubair);
    AddChild(zubairBinAwwam, urwahBinZubair);

    AddChild(arwaBintiKurayz, utsmanBinAffan);
    AddChild(arwaBintiKurayz, amnaBintiAffan);

    /* G3 → G4 (anak Fatimah) */
    AddChild(fatimah, hasan);
    AddChild(fatimah, husain);

    return abdulMuthalib;
}

// void CekHijabMahjub(address pewaris)
// {
    
// }
// void KalkulasiWarisan(address pewaris, float totalHarta)
// {
    
// }
static void CetakRingkasanRec(Tree T)
{
    if (T == NULL)
        return;

    if (T->info.Aktif)
    {
        const char *status;
        if (!T->info.Hidup)
            status = "WAFAT (pewaris)";
        else if (T->info.Mahjub)
            status = "MAHJUB";
        else
            status = "BERHAK";

        printf("  %-25s | %-6s | %s\n",
               T->info.Nama,
               T->info.Gender ? "L" : "P",
               status);
    }

    CetakRingkasanRec(T->ps_fs);
    CetakRingkasanRec(T->ps_nb);
}

void CetakRingkasanAhliWaris(Tree T)
{
    printf("\n=== RINGKASAN STATUS AHLI WARIS ===\n");
    printf("  %-25s | Gender | Status\n", "Nama");
    printf("  %s\n", "--------------------------------------------");
    CetakRingkasanRec(T);
}


int main()
{
    Tree silsilah;
    Create_tree(&silsilah);

    printf("============================================\n");
    printf("  SISTEM FARAIDH — NON BINARY TREE          \n");
    printf("  Silsilah Keluarga Rasulullah SAW          \n");
    printf("============================================\n\n");

    silsilah = BangunSilsilah();
    printf("     Total anggota : %d node\n", NbElmt(silsilah));
    printf("     Kedalaman tree : %d level\n\n", Depth(silsilah));

    address pewaris = NULL;
    float totalHarta = 0.0f;
    int sudahInput = 0; /* flag: apakah input sudah dilakukan */

    int pilihan;
    do
    {
        printf("\n============================================\n");
        printf("  MENU UTAMA                               \n");
        printf("============================================\n");
        printf("  1. Tampilkan Struktur Pohon Keluarga\n");
        printf("  2. Pilih Pewaris & Input Harta\n");
        printf("  3. Input Status Anggota Keluarga\n");
        printf("  4. Cek Hijab & Mahjub\n");
        printf("  5. Tampilkan Ringkasan Ahli Waris\n");
        printf("  6. Hitung & Tampilkan Pembagian Warisan\n");
        printf("  7. Traversal Pohon\n");
        printf("  0. Keluar\n");
        printf("--------------------------------------------\n");

        /* Tampilkan pewaris aktif jika sudah dipilih */
        if (pewaris != NULL)
            printf("  [Pewaris aktif : %s | Harta : Rp %.2f]\n",
                   pewaris->info.Nama, totalHarta);

        printf("Pilih menu: ");
        if (scanf("%d", &pilihan) != 1)
        {
            while (getchar() != '\n')
                ;
            pilihan = -1;
        }

        switch (pilihan)
        {
            /* -------------------------------------------------- */
            case 1:
                system("cls"); /* bersihkan layar (Windows) */
                printf("\n=== STRUKTUR POHON KELUARGA ===\n");
                PrintTree(silsilah);
                break;
            
            case 2:
                printf("\n=== DAFTAR ANGGOTA KELUARGA ===\n");
                PrintTree(silsilah);
                // CetakDaftarNama(silsilah, 0);

                char namaPewaris[50];
                printf("\nMasukkan nama pewaris (sesuai daftar): ");
                while (getchar() != '\n')
                    ;
                if (fgets(namaPewaris, sizeof(namaPewaris), stdin) == NULL)
                {
                    printf("Gagal membaca input.\n");
                    break;
                }
                namaPewaris[strcspn(namaPewaris, "\n")] = '\0';

                address hasil = SearchPewaris(silsilah, namaPewaris);
                if (hasil == NULL)
                {
                    printf("Nama '%s' tidak ditemukan.\n", namaPewaris);
                    break;
                }

                /* Reset flag jika pewaris diganti */
                if (pewaris != hasil)
                    sudahInput = 0;
                pewaris = hasil;

                printf("Pewaris : %s (Level %d)\n",
                    pewaris->info.Nama,
                    Level(silsilah, pewaris->info));

                printf("Masukkan total harta warisan (Rp): ");
                if (scanf("%f", &totalHarta) != 1 || totalHarta <= 0)
                {
                    printf("Input harta tidak valid.\n");
                    totalHarta = 0.0f;
                    pewaris = NULL;
                    break;
                }
                printf("Harta Rp %.2f berhasil disimpan.\n", totalHarta);
                /* 5. Input status keluarga */
                AktivasiDanInput(pewaris);

                /* 6. Pengecekan hijab & mahjub */
                CekHijabMahjub(pewaris);
                /* 7. Tampilkan ringkasan status */
                CetakRingkasanAhliWaris(silsilah);

                /* 8. Hitung & tampilkan pembagian warisan */
                KalkulasiWarisan(pewaris, totalHarta);

                break;

            default:
                printf("Pilihan tidak valid. Masukkan angka 0-7.\n");
                break;
        }
    } while (pilihan != 0);

    return 0;
}
