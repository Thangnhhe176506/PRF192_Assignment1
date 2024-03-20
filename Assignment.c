#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Ðinh nghia cau truc du lieu SinhVien

typedef struct 
{
    char ten[50];// Ten cua sinh vien
    int tuoi;// Tuoi cua sinh vien
    float diem;// Ðiem cua sinh vien
} 
SinhVien;
// Ham de them mot sinh viên moi vao file
void themSinhVien(SinhVien newStudent, FILE *file)
{
	// Ghi thong tin cua sinh vien vào file
    fwrite(&newStudent, sizeof(SinhVien), 1, file);
}
// Hàm de hien thi thông tin cua tat ca sinh viên trong file

void hienThiSinhVien(FILE *file)
{
    SinhVien tempStudent;
    rewind(file);// Ðat con tro ve dau file
    while (fread(&tempStudent, sizeof(SinhVien), 1, file)) 
	{
		// In ra thông tin cua tung sinh viên
        printf("Ten: %s\n", tempStudent.ten);
        printf("Tuoi: %d\n", tempStudent.tuoi);
        printf("Diem: %.2f\n", tempStudent.diem);
        printf("-------------------\n");
    }
}

// Ham de cap nhtt thông tin cua mot sinh viên trong file
void capNhatSinhVien(char *name, SinhVien updatedStudent, FILE *file) 
{
    SinhVien tempStudent;
    int found = 0;
    long int currentPosition;
    rewind(file);// Ðat con tro ve dau file
    while (fread(&tempStudent, sizeof(SinhVien), 1, file))
	{
        if (strcmp(tempStudent.ten, name) == 0) // Neu tên trung khop
		{
            currentPosition = ftell(file) - sizeof(SinhVien);// Luu vi tri hien thi cua con tro
            fseek(file, currentPosition, SEEK_SET); // Ðat con tro tai vi trí cua sinh viên can cap nhat
            fwrite(&updatedStudent, sizeof(SinhVien), 1, file); // Ghi thông tin cua sinh vien moi vao file
            found = 1;  // Ðanh dau da tim thay sinh viên can cap nhat
            break;
            found = 1;
            break;
        }
    }
    if (!found)
	{
        printf("Khong tim thay sinh vien.\n");// Thong bao neu không tìm thay sinh viên can cap nhat
    }
}

// Hàm de xóa mot sinh viên khoi file
void xoaSinhVien(char *name, FILE *file) 
{
    SinhVien tempStudent;
    FILE *tempFile = fopen("temp.txt", "wb"); // Mo mot file tam de ghi du lieu
    int found = 0;
    rewind(file);// Ðat con tro ve dau file
    while (fread(&tempStudent, sizeof(SinhVien), 1, file))
	 {
        if (strcmp(tempStudent.ten, name) != 0)  // Neu ten khong trung khop
   
		{
            fwrite(&tempStudent, sizeof(SinhVien), 1, tempFile); // Ghi du lieu cua sinh viên vao file tam
        } else 
		{
            found = 1;// Ðanh dau dã tìm thay sinh viên can xóa
        }
    }
    fclose(file);// Ðóng file goc
    fclose(tempFile);// Ðóng file tam
    remove("students.txt");// Xóa file goc
    rename("temp.txt", "students.txt");// Ðoi tên file tam thành tên file goc
    if (!found) {
        printf("Khong tim thay sinh vien.\n"); // Thông báo neu không tìm thay sinh viên can xóa
    } else {
        printf("Xoa sinh vien thanh cong.\n");// Thông báo khi xóa sinh viên thành công
    }
}

int main() {
    FILE *file = fopen("students.txt", "ab+");// Mo hoac tao file de doc và ghi
    if (file == NULL) {
        printf("Loi khi mo file.\n");// Thông báo loi neu không mo duoc file
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
                themSinhVien(newStudent, file);// Goi ham de thêm sinh viên moi vào file
                break;
            case 2:
                printf("Danh sach sinh vien:\n");
                hienThiSinhVien(file);// Goi hàm de hien thi thông tin cua tat ca sinh viên trong file
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
                capNhatSinhVien(name, updatedStudent, file);// Goi hàm de cap nhat thông tin cua sinh viên
                break;
            case 4:
                printf("Nhap ten sinh vien can xoa: ");
                scanf("%s", name);
                xoaSinhVien(name, file); // Goi ham de xaa sinh viên khoi file
                break;
            case 5:
                printf("Dang thoat...\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");// Thông bao neu lua chon không hop le
        }
    } while (choice != 5);// Lap lai menu cho den khi nguoi dùng chon thoát

    fclose(file);// Ðóng file
    return 0;
}
