#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
typedef struct{

    char isim[100];
    long int kod;
    long int alankodu;
    long int numara;


}rehber;

int menubas();
int kayitekle(FILE *dosya,long int kod);
void kayitlistele(FILE *dosya);
void kayitduzenle(FILE *dosya);
void nilekayit(FILE *dosya);
void iilekayit(FILE *dosya);
void kayitsil(FILE *dosya);
int main()
{
    setlocale(LC_ALL, "Turkish");
    int secim,sonuc;
    long int kod=0;
    FILE *fp;
    fp=fopen("rehber.txt","wb+");




    while(1){

        secim=menubas();

        switch(secim){

        case 1:
            kod++;
            sonuc=kayitekle(fp,kod);
            if(sonuc==0){
                kod--;
                printf("Yazma hatasý oluþtu lütfen tekrar deneyiniz ...\n");


            }
            else{

                printf("Kayýt Baþarýyla eklendi...\n");
                rewind(fp);

            }
            break;
        case 2:
            kayitlistele(fp);
            rewind(fp);
            break;
        case 3:
            kayitduzenle(fp);
            rewind(fp);
            break;
        case 4:
            nilekayit(fp);
            rewind(fp);
            break;
        case 5:
            iilekayit(fp);
            rewind(fp);
            break;
        case 6:
            kayitsil(fp);
            rewind(fp);
            break;
        case 0:
            exit(1);
            break;
        default:
            printf("Lütfen doðru iþlemi seçiniz .");
            break;

        }

    }

    return 0;
}
void kayitsil(FILE *dosya){

    long int ikod;
    rehber tut,gonder,tut1;
    int varmi;
    gonder.alankodu=0;
    strcpy(gonder.isim,"");
    gonder.kod=0;
    gonder.numara=0;
    printf("Silmek istediðiniz kodu giriniz : ");
    scanf("%ld",&ikod);
    while((fread(&tut,sizeof(tut),1,dosya))==1){

        if(tut.kod==ikod){
            varmi++;
            gonder.kod=ikod;
            fseek(dosya,(ikod-1)*sizeof(tut),SEEK_SET);
            if((fwrite(&gonder,sizeof(gonder),1,dosya))!=1){

                printf("Kayýt silinirken bir hata oluþtu...");
                break;

            }
            else{
                printf("kayit baþarýyla silindi.\n");
                break;


            }

        }


    }
    if(varmi==0){

        printf("böyle bir kayit bulunmamaktadýr...\n");

    }



}
int menubas(){
    int secim;
    printf("TELEFON REHBERÝ V1.0\n\n");

    printf("ÝÞLEMLER\n");

    printf("1. Kayýt ekle\n");
    printf("2. Telefonlarý Listele\n");
    printf("3. Kaydý Düzenle\n");
    printf("4. Numara ile Kayýt Bul\n");
    printf("5. Ýsim ile Kayýt Bul\n");
    printf("6. Kayýt Sil\n");
    printf("0. Çýkýþ\n");
    printf("Seçim :");
    scanf("%d",&secim);

    return secim;


}
int kayitekle(FILE *dosya,long int kod){

    rehber kayit;
    // Kayitlari al

    kayit.kod=kod;
    printf("Ýsimi giriniz :");
    scanf("%s",kayit.isim);
    printf("Alan kodunu giriniz (örn:539) : ");
    scanf("%ld",&kayit.alankodu);
    printf("Numarayý giriniz :");
    scanf("%ld",&kayit.numara);


    // Dosyaya Kaydet

    fseek(dosya,(kod-1)*sizeof(kayit),SEEK_SET);
    if((fwrite(&kayit,sizeof(kayit),1,dosya))!=1){

        return 0;

    }
    else{

        return 1;

    }

}
void kayitlistele(FILE *dosya){

    rehber tut;
    while((fread(&tut,sizeof(tut),1,dosya))==1){
        if(tut.numara==0){


        }else{
        printf("Kod : %ld\n",tut.kod);
        printf("Ýsim : %s\n",tut.isim);
        printf("Alan Kodu : %ld\n",tut.alankodu);
        printf("Numara: %ld\n",tut.numara);
        }

    }

}
void kayitduzenle(FILE *dosya){

    char isim[100];
    int varmi;
    rehber tut,gonder;
    long int kod;
    gonder.alankodu=0;
    strcpy(gonder.isim,"");
    gonder.numara=0;
    gonder.kod=0;
    printf("Düzenlemek istediðiniz isimi giriniz : ");
    scanf("%s",isim);
    while((fread(&tut,sizeof(tut),1,dosya))==1){

        if(strcmp(isim,tut.isim)==0){
            varmi++;
            kod=tut.kod;
            fseek(dosya,(kod-1)*sizeof(tut),SEEK_SET);
            fwrite(&gonder,sizeof(gonder),1,dosya);

            printf("Yeni isimi giriniz : ");
            scanf("%s",gonder.isim);
            printf("Yeni alan kodunu giriniz :");
            scanf("%ld",&gonder.alankodu);
            printf("Yeni numarayi giriniz : ");
            scanf("%ld",&gonder.numara);
            gonder.kod=kod;
            fseek(dosya,(kod-1)*sizeof(gonder),SEEK_SET);
            if((fwrite(&gonder,sizeof(gonder),1,dosya))!=1){

                printf("Güncelleme sýrasýnda bir hata oluþtu...\n");
                break;
            }
            else{

                printf("Kayit baþarýyla güncellendi...\n");
                break;

            }



        }


    }
    if(varmi==0){

        printf("böyle bir kayýt bulunmamaktadýr.");

    }



}
void nilekayit(FILE *dosya){

    long int numara;
    rehber tut;
    int varmi;
    printf("Aramak istediðiniz numarayý giriniz :");
    scanf("%ld",&numara);
    while((fread(&tut,sizeof(tut),1,dosya))==1){

        if(tut.numara==numara){
            varmi++;
            printf("Kod : %ld\n",tut.kod);
            printf("Ýsim : %s\n",tut.isim);
            printf("Alan Kodu : %ld\n",tut.alankodu);
            printf("Numara: %ld\n",tut.numara);

        }

    }
    if(varmi==0){

        printf("böyle bir kayit bulunmamaktadýr...\n");

    }

}
void iilekayit(FILE *dosya){

    char isim[100];
    rehber tut;
    int varmi;
    printf("Aramak istediðiniz isimi giriniz : ");
    scanf("%s",isim);
    while((fread(&tut,sizeof(tut),1,dosya))==1){

        if(strcmp(isim,tut.isim)==0){

            printf("Kod : %ld\n",tut.kod);
            printf("Ýsim : %s\n",tut.isim);
            printf("Alan Kodu : %ld\n",tut.alankodu);
            printf("Numara: %ld\n",tut.numara);

        }

    }
    if(varmi==0){

        printf("böyle bir kayit bulunmamaktadýr...\n");

    }

}
