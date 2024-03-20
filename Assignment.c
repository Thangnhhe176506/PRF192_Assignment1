#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// �inh nghia cau truc du lieu SinhVien

typedef struct 
{
    char ten[50];// Ten cua sinh vien
    int tuoi;// Tuoi cua sinh vien
    float diem;// �iem cua sinh vien
} 
SinhVien;
// Ham de them mot sinh vi�n moi vao file
void themSinhVien(SinhVien newStudent, FILE *file)
{
	// Ghi thong tin cua sinh vien v�o file
    fwrite(&newStudent, sizeof(SinhVien), 1, file);
}
// H�m de hien thi th�ng tin cua tat ca sinh vi�n trong file

void hienThiSinhVien(FILE *file)
{
    SinhVien tempStudent;
    rewind(file);// �at con tro ve dau file
    while (fread(&tempStudent, sizeof(SinhVien), 1, file)) 
	{
		// In ra th�ng tin cua tung sinh vi�n
        printf("Ten: %s\n", tempStudent.ten);
        printf("Tuoi: %d\n", tempStudent.tuoi);
        printf("Diem: %.2f\n", tempStudent.diem);
        printf("-------------------\n");
    }
}

// Ham de cap nhtt th�ng tin cua mot sinh vi�n trong file
void capNhatSinhVien(char *name, SinhVien updatedStudent, FILE *file) 
{
    SinhVien tempStudent;
    int found = 0;
    long int currentPosition;
    rewind(file);// �at con tro ve dau file
    while (fread(&tempStudent, sizeof(SinhVien), 1, file))
	{
        if (strcmp(tempStudent.ten, name) == 0) // Neu t�n trung khop
		{
            currentPosition = ftell(file) - sizeof(SinhVien);// Luu vi tri hien thi cua con tro
            fseek(file, currentPosition, SEEK_SET); // �at con tro tai vi tr� cua sinh vi�n can cap nhat
            fwrite(&updatedStudent, sizeof(SinhVien), 1, file); // Ghi th�ng tin cua sinh vien moi vao file
            found = 1;  // �anh dau da tim thay sinh vi�n can cap nhat
            break;
            found = 1;
            break;
        }
    }
    if (!found)
	{
        printf("Khong tim thay sinh vien.\n");// Thong bao neu kh�ng t�m thay sinh vi�n can cap nhat
    }
}

// H�m de x�a mot sinh vi�n khoi file
void xoaSinhVien(char *name, FILE *file) 
{
    SinhVien tempStudent;
    FILE *tempFile = fopen("temp.txt", "wb"); // Mo mot file tam de ghi du lieu
    int found = 0;
    rewind(file);// �at con tro ve dau file
    while (fread(&tempStudent, sizeof(SinhVien), 1, file))
	 {
        if (strcmp(tempStudent.ten, name) != 0)  // Neu ten khong trung khop
   
		{
            fwrite(&tempStudent, sizeof(SinhVien), 1, tempFile); // Ghi du lieu cua sinh vi�n vao file tam
        } else 
		{
            found = 1;// �anh dau d� t�m thay sinh vi�n can x�a
        }
    }
    fclose(file);// ��ng file goc
    fclose(tempFile);// ��ng file tam
    remove("students.txt");// X�a file goc
    rename("temp.txt", "students.txt");// �oi t�n file tam th�nh t�n file goc
    if (!found) {
        printf("Khong tim thay sinh vien.\n"); // Th�ng b�o neu kh�ng t�m thay sinh vi�n can x�a
    } else {
        printf("Xoa sinh vien thanh cong.\n");// Th�ng b�o khi x�a sinh vi�n th�nh c�ng
    }
}

int main() {
    FILE *file = fopen("students.txt", "ab+");// Mo hoac tao file de doc v� ghi
    if (file == NULL) {
        printf("Loi khi mo file.\n");// Th�ng b�o loi neu kh�ng mo duoc file
        return 1;
    }

    int choice;
    char name[50];
    SinhVien newStudent, updatedStudent;

    do
	 {
        printf("Menu:\n");
        printf("1. Them sinh vien\n");
        printf("2. Hien thi tat ca sinh vien\n");
        printf("3. Cap nhat thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) 
		{
            case 1:
                printf("Nhap ten: ");
                scanf("%s", newStudent.ten);
                printf("Nhap tuoi: ");
                scanf("%d", &newStudent.tuoi);
                printf("Nhap diem: ");
                scanf("%f", &newStudent.diem);
                themSinhVien(newStudent, file);// Goi ham de th�m sinh vi�n moi v�o file
                break;
            case 2:
                printf("Danh sach sinh vien:\n");
                hienThiSinhVien(file);// Goi h�m de hien thi th�ng tin cua tat ca sinh vi�n trong file
                break;
            case 3:
                printf("Nhap ten sinh vien can cap nhat: ");
                scanf("%s", name);
                printf("Nhap ten moi: ");
                scanf("%s", updatedStudent.ten);
                printf("Nhap tuoi moi: ");
                scanf("%d", &updatedStudent.tuoi);
                printf("Nhap diem moi: ");
                scanf("%f", &updatedStudent.diem);
                capNhatSinhVien(name, updatedStudent, file);// Goi h�m de cap nhat th�ng tin cua sinh vi�n
                break;
            case 4:
                printf("Nhap ten sinh vien can xoa: ");
                scanf("%s", name);
                xoaSinhVien(name, file); // Goi ham de xaa sinh vi�n khoi file
                break;
            case 5:
                printf("Dang thoat...\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");// Th�ng bao neu lua chon kh�ng hop le
        }
    } while (choice != 5);// Lap lai menu cho den khi nguoi d�ng chon tho�t

    fclose(file);// ��ng file
    return 0;
}
