#include<stdio.h>
#include<string.h>

struct Book {
	char Id[20];
    char title[100];
    char author[50];
    float price; 
    char genre[50]; 
};

struct Book b[100];
int bookCount = 0;

void inputBook(struct Book* b) {
	printf("Nhap ma sach: ");
    scanf("%s", b->Id);
    getchar();
    
    printf("Nhap ten sach: ");
    fgets(b->title, sizeof(b->title), stdin);
    b->title[strcspn(b->title, "\n")] = 0;
    
    printf("Nhap tac gia: ");
    fgets(b->author, sizeof(b->author), stdin);
    b->author[strcspn(b->author, "\n")] = 0;
    
    printf("Nhap gia tien: ");
    scanf("%f", &b->price);
    getchar();
    
    printf("Nhap the loai: ");
    fgets(b->genre, sizeof(b->genre), stdin);
    b->genre[strcspn(b->genre, "\n")] = 0;
}

void displayBooks() {
	for (int i = 0; i < bookCount; i++) {
        printf("\nMa sach: %s\n", b[i].Id);
        printf("Ten sach: %s\n", b[i].title);
        printf("Tac gia: %s\n", b[i].author);
        printf("Gia tien: %.2f\n", b[i].price);
        printf("The loai: %s\n", b[i].genre);
    }
}

void addBook(int pos, struct Book* b) {
	for (int i = bookCount; i > pos; i--) {
        b[i] = b[i - 1];
    }
    b[pos] = *b;
    bookCount++;
}

void deleteBook(char* Id) {
	int index=-1;
	for(int i=0; i<bookCount; i++) {
		if(strcmp(b[i].Id, Id)){
			index=i;
			break;
		}
	}
	if (index == -1) {
        printf("Sach voi ma sach '%s' khong ton tai.\n", Id);
        return;
    }
    for(int i=index; i<bookCount-1;i++) {
    	b[i] = b[i+1];
	}
	bookCount--;
}
	
void updateBook(char* Id) {
	int index=-1;
	for (int i = 0; i < bookCount; i++) {
        if (strcmp(b[i].Id, Id) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Sach voi ma sach '%s' khong ton tai.\n", Id);
        return;
    }
    printf("Cap nhat thong tin sach:\n");
    inputBook(&b[index]);
}

void sapXep(int ascending) {
	for (int i = 0; i < bookCount - 1; i++) {
        for (int j = i + 1; j < bookCount; j++) {
            if ((ascending && b[i].price > b[j].price) || (!ascending && b[i].price < b[j].price)) {
                struct Book temp = b[i];
                b[i] = b[j];
                b[j] = temp;
            }
        }
    }
    printf("Sap xep hoan tat.\n");
}

void search(char* title) {
	int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strstr(b[i].title, title) != NULL) {
            printf("\nMa sach: %s\n", b[i].Id);
            printf("Ten sach: %s\n", b[i].title);
            printf("Tac gia: %s\n", b[i].author);
            printf("Gia tien: %.2f\n", b[i].price);
            printf("The loai: %s\n", b[i].genre);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong tim thay sach voi ten '%s'.\n", title);
    }
}

int main() {
	int choice;
    do {
        printf("\nMENU\n");
        printf("1. Nhap so luong va thong tin sach\n");
        printf("2. Hien thi thong tin sach\n");
        printf("3. Them sach vao vi tri\n");
        printf("4. Xaa sach theo ma sach\n");
        printf("5. Cap nhat thong tin sach theo ma sach\n");
        printf("6. Sap xep sach theo gia (tang/giam)\n");
        printf("7. Tim kiem sach theo ten sach\n");
        printf("8. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1: {
                printf("Nhap so luong sách: ");
                scanf("%d", &bookCount);
                for (int i = 0; i < bookCount; i++) {
                    printf("\nNhap thong tin sach %d:\n", i + 1);
                    inputBook(&b[i]);
                }
                break;
            }
            case 2:
                displayBooks();
                break;
            case 3: {
                int pos;
                struct Book newBook;
                printf("Nhap vi tri can them: ");
                scanf("%d", &pos);
                getchar(); 
                printf("Nhap thong tin sach can them:\n");
                inputBook(&newBook);
                addBook(pos, &newBook);
                break;
            }
            case 4: {
                char Id[20];
                printf("Nhap ma sach can xoa: ");
                scanf("%s", Id);
                deleteBook(Id);
                break;
            }
            case 5: {
                char Id[20];
                printf("Nhap ma sach can cap nhat: ");
                scanf("%s", Id);
                updateBook(Id);
                break;
            }
            case 6: {
                int choiceSort;
                printf("Sap xep sach theo gia:\n");
                printf("1. Tang dan\n");
                printf("2. Giam dan\n");
                printf("Chan: ");
                scanf("%d", &choiceSort);
                if (choiceSort == 1)
                    sapXep(1);
                else
                    sapXep(0);
                break;
            }
            case 7: {
                char title[100];
                printf("Nhap ten sach can tim kiem: ");
                getchar();
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;
                sapXep(title);
                break;
            }
            case 8:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Vui long chon lai.\n");
        }
    } while (choice != 8);
	
	return 0;
}

