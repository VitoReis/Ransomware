#include <stdio.h>
#include <stdlib.h>


int encrypt(){
    int key = rand() + 1;
    FILE *originalPointer, *encryptedPointer;

    originalPointer = fopen("toEncrypt.txt", "r");
    if(originalPointer == NULL) return 0;
    encryptedPointer = fopen("encrypted.txt", "w");
    if(encryptedPointer == NULL) return 0;

    for(char c = fgetc(originalPointer); c != EOF; c = fgetc(originalPointer)){
        c += key;
        fputc(c, encryptedPointer);
    }
    fclose(originalPointer);
    fclose(encryptedPointer);

    if(remove("toEncrypt.txt") != 0) return 0;
    if(rename("encrypted.txt", "toEncrypt.txt") != 0) return 0;
    return key;
}


int decrypt(int key){
    int userKey;
    printf("What is the key? ");
    scanf("%d", &userKey);
    userKey == key ? : printf("\nInvalid key\n");
    FILE *originalPointer, *encryptedPointer;

    originalPointer = fopen("toEncrypt.txt", "r");
    if(originalPointer == NULL) return 1;
    encryptedPointer = fopen("encrypted.txt", "w");
    if(encryptedPointer == NULL) return 1;

    for(char c = fgetc(originalPointer); c != EOF; c = fgetc(originalPointer)){
        c -= key;
        fputc(c, encryptedPointer);
    }
    fclose(originalPointer);
    fclose(encryptedPointer);
    
    if(remove("toEncrypt.txt") != 0) return 1;
    if(rename("encrypted.txt", "toEncrypt.txt") != 0) return 1;
    return 0;
}


void main(){
    int choice = 1, success = 0;
    do{
        printf("Do you want to:\n1 - Encryt the file\n2 - Decrypt the file\n3 - Exit\n> ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                if(success){
                    printf("Your file is already encrypted\n");
                    break;
                }
                success = encrypt();
                success ? printf("Your file has been encrypted\n") : printf("ERROR: Your file was not been encrypted\n");
            break;
            case 2:
                if(!success){
                    printf("Your file is already decrypted\n");
                    break;
                }
                success = decrypt(success);
                !success ? printf("Your file has been decrypted\n") : printf("ERROR: Your file was not been decrypted\n");
            break;
            case 3:
            break;
            default:
                printf("\nOption unavailable\n");
            break;
        }
    }while(choice != 3);
}
