#include<stdio.h>
#include<string.h>

struct Product {
    char Id[20];    
    char name[100];        
    float costPrice;       
    float salePrice;       
    int quantity;
};

struct Product p[100];
float revenue = 0;
int productCount = 0;

void inputProduct(struct Product* p) {
    printf("Nhap ma san pham: ");
    scanf("%s", p->Id);
    getchar(); 

    printf("Nhap ten san pham: ");
    fgets(p->name, sizeof(p->name), stdin);
    p->name[strcspn(p->name, "\n")] = 0; 

    printf("Nhap gia nhap: ");
    scanf("%f", &p->costPrice);

    printf("Nhap gia ban: ");
    scanf("%f", &p->salePrice);

    printf("Nhap so luong: ");
    scanf("%d", &p->quantity);
}

void displayProducts() {
    for (int i = 0; i < productCount; i++) {
        printf("\nMa san pham: %s\n", p[i].Id);
        printf("Ten san pham: %s\n", p[i].name);
        printf("Gia nhap: %.2f\n", p[i].costPrice);
        printf("Gia ban: %.2f\n", p[i].salePrice);
        printf("So luong: %d\n", p[i].quantity);
    }
}

void enterProduct() {
    struct Product newProduct;
    int found = 0;

    inputProduct(&newProduct);
 
    for (int i = 0; i < productCount; i++) {
        if (strcmp(p[i].Id, newProduct.Id) == 0) {
            p[i].quantity += newProduct.quantity; 
            found = 1;
            break;
        }
    }

    if (!found) {
        p[productCount] = newProduct;
        productCount++;
    }
    
    revenue -= newProduct.quantity * newProduct.costPrice;
}

void updateProduct(char* Id) {
    int index = -1;

    for (int i = 0; i < productCount; i++) {
        if (strcmp(p[i].Id, Id) == 0) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("San pham voi ma '%s' khong ton tai.\n", Id);
        return;
    }

    printf("Cap nhat thong tin san pham:\n");
    inputProduct(&p[index]);
}

void sortProducts(int ascending) {
    for (int i = 0; i < productCount - 1; i++) {
        for (int j = i + 1; j < productCount; j++) {
            if ((ascending && p[i].salePrice > p[j].salePrice) ||
                (!ascending && p[i].salePrice < p[j].salePrice)) {
                struct Product temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    printf("Sap xep hoan tat.\n");
}

void searchProduct(char* name) {
    int found = 0;
    for (int i = 0; i < productCount; i++) {
        if (strstr(p[i].name, name) != NULL) {
            printf("\nMa san pham: %s\n", p[i].Id);
            printf("Ten san pham: %s\n", p[i].name);
            printf("Gia nhap: %.2f\n", p[i].costPrice);
            printf("Gia ban: %.2f\n", p[i].salePrice);
            printf("So luong: %d\n", p[i].quantity);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong tim thay san pham voi ten '%s'.\n", name);
    }
}

void sellProduct() {
    char Id[20];
    int quantityToSell;
    
    printf("Nhap ma san pham can ban: ");
    scanf("%s", Id);
    
    printf("Nhap so luong san pham can ban: ");
    scanf("%d", &quantityToSell);
    
    int index = -1;
    
    for (int i = 0; i < productCount; i++) {
        if (strcmp(p[i].Id, Id) == 0) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("San pham voi ma '%s' khong ton tai.\n", Id);
        return;
    }

    if (p[index].quantity == 0) {
        printf("San pham da het hang.\n");
        return;
    }
    
    if (quantityToSell > p[index].quantity) {
        printf("Khong du hang de ban.\n");
        return;
    }
    
    p[index].quantity -= quantityToSell;
    revenue += quantityToSell * p[index].salePrice;
    
    printf("Ban thanh cong %d san pham %s. Doanh thu hien tai: %.2f\n", quantityToSell, p[index].name, revenue);
}

void displayRevenue() {
    printf("Doanh thu hien tai: %.2f\n", revenue);
}

int main() {
	int choice;
    do {
        printf("\nMENU\n");
        printf("1. Nhap so luong va thong tin san pham\n");
        printf("2. Hien thi danh sach san pham\n");
        printf("3. Nhap san pham\n");
        printf("4. Cap nhat thong tin san pham\n");
        printf("5. Sap xep san pham theo gia (tang/giam)\n");
        printf("6. Tim kiem san pham\n");
        printf("7. Ban san pham\n");
        printf("8. Doanh thu hien tai\n");
        printf("9. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                printf("Nhap so luong san pham: ");
                scanf("%d", &productCount);
                for (int i = 0; i < productCount; i++) {
                    printf("\nNhap thong tin san pham %d:\n", i + 1);
                    inputProduct(&p[i]);
                }
                break;
            case 2:
                displayProducts();
                break;
            case 3:
                enterProduct();
                break;
            case 4: {
                char Id[20];
                printf("Nhap ma san pham can cap nhat: ");
                scanf("%s", Id);
                updateProduct(Id);
                break;
            }
            case 5: {
                int choiceSort;
                printf("Sap xep san pham theo gia:\n");
                printf("1. Tang dan\n");
                printf("2. Giam dan\n");
                printf("Chan: ");
                scanf("%d", &choiceSort);
                if (choiceSort == 1)
                    sortProducts(1);
                else
                    sortProducts(0);
                break;
            }
            case 6: {
                char name[100];
                printf("Nhap ten san pham can tim kiem: ");
                getchar(); 
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;  
                searchProduct(name);
                break;
            }
            case 7:
                sellProduct();
                break;
            case 8:
                displayRevenue();
                break;
            case 9:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Vui long chon lai.\n");
        }
    } while (choice != 9);
	
	return 0;
}

