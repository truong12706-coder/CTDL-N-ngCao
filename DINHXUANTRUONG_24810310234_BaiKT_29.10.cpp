
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Ngay {
    int ngay, thang, nam;
};

struct HangHoa {
    string ma;
    string ten;
    Ngay ngayXuat;
    double gia;
};

void Nhap(HangHoa a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "\nNhap hang hoa thu " << i + 1 << ":\n";

        cout << "Ma hang hoa: ";
        cin >> ws;
        getline(cin, a[i].ma);

        cout << "Ten hang hoa: ";
        getline(cin, a[i].ten);

        char dau1, dau2;
        cout << "Ngay xuat (dd/mm/yyyy): ";
        cin >> a[i].ngayXuat.ngay >> dau1
            >> a[i].ngayXuat.thang >> dau2
            >> a[i].ngayXuat.nam;

        cout << "Gia xuat hang (trieu dong): ";
        cin >> a[i].gia;
    }
}

void XuatMot(HangHoa h) {
    cout << left << setw(12) << h.ma
         << setw(25) << h.ten;

    cout << setfill('0')
         << setw(2) << h.ngayXuat.ngay << "/"
         << setw(2) << h.ngayXuat.thang << "/"
         << setw(4) << h.ngayXuat.nam;

    cout << setfill(' ') << "     "
         << fixed << setprecision(2)
         << h.gia << endl;
}

void Xuat(HangHoa a[], int n) {
    cout << left
         << setw(12) << "Ma hang"
         << setw(25) << "Ten hang"
         << setw(15) << "Ngay xuat"
         << "Gia (trieu dong)" << endl;

    for (int i = 0; i < n; i++) {
        XuatMot(a[i]);
    }
}

void HoanVi(HangHoa &a, HangHoa &b) {
    HangHoa tam = a;
    a = b;
    b = tam;
}

int PhanHoach(HangHoa a[], int left, int right) {
    double chot = a[right].gia;
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (a[j].gia <= chot) {
            i++;
            HoanVi(a[i], a[j]);
        }
    }

    HoanVi(a[i + 1], a[right]);
    return i + 1;
}

void QuickSort(HangHoa a[], int left, int right) {
    if (left < right) {
        int p = PhanHoach(a, left, right);

        QuickSort(a, left, p - 1);
        QuickSort(a, p + 1, right);
    }
}

void TimKiem(HangHoa a[], int n, double X) {
    int left = 0;
    int right = n - 1;
    int vt = -1;

    // Tim mot vi tri co gia bang X
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (a[mid].gia == X) {
            vt = mid;
            break;
        } else if (a[mid].gia < X) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (vt == -1) {
        cout << "\nKhong tim thay hang hoa co gia bang "
             << fixed << setprecision(2) << X << endl;
        return;
    }

    int dau = vt;
    while (dau > 0 && a[dau - 1].gia == X) {
        dau--;
    }

    // Hien thi tat ca hang hoa co gia bang X
    cout << "\nDanh sach hang hoa co gia bang "
         << fixed << setprecision(2) << X << ":\n";

    cout << left
         << setw(12) << "Ma hang"
         << setw(25) << "Ten hang"
         << setw(15) << "Ngay xuat"
         << "Gia (trieu dong)" << endl;

    int i = dau;
    while (i < n && a[i].gia == X) {
        XuatMot(a[i]);
        i++;
    }
}

int main() {
    HangHoa a[100];
    int n;
    double X;

    // Nhap so luong hang hoa
    cout << "Nhap so luong hang hoa n (1-100): ";
    cin >> n;

    if (n < 1 || n > 100) {
        cout << "So luong hang hoa khong hop le!" << endl;
        return 0;
    }

    // Nhap va xuat danh sach ban dau
    Nhap(a, n);

    cout << "\nDANH SACH HANG HOA VUA NHAP:\n";
    Xuat(a, n);

    // Sap xep tang dan theo gia
    QuickSort(a, 0, n - 1);

    cout << "\nDANH SACH HANG HOA SAU KHI SAP XEP:\n";
    Xuat(a, n);

    // Nhap gia can tim
    cout << "\nNhap gia X can tim (trieu dong): ";
    cin >> X;

    // Tim kiem nhi phan
    TimKiem(a, n, X);

    return 0;
}

