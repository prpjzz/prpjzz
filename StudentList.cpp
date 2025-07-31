#include<bits/stdc++.h>
using namespace std;


class SinhVien {
private:
    string maSV;
    string hoTen;
    float diemTB;

public:

    SinhVien() : maSV(""), hoTen(""), diemTB(0.0) {}
    SinhVien(string ma, string ten, float diem) : maSV(ma), hoTen(ten), diemTB(diem) {}

    string getMaSV() const { return maSV; }
    string getHoTen() const { return hoTen; }
    float getDiemTB() const { return diemTB; }

    void setMaSV(const string& ma) { maSV = ma; }
    void setHoTen(const string& ten) { hoTen = ten; }
    void setDiemTB(float diem) { diemTB = diem; }

    bool operator>(const SinhVien& other) const {
        return diemTB > other.diemTB;
    }


    void nhap() {
        cout << "Nhap ma sinh vien: ";
        getline(cin, maSV);
        cout << "Nhap ho ten: ";
        getline(cin, hoTen);
        cout << "Nhap diem trung binh: ";
        cin >> diemTB;
        cin.ignore();
    }

    void hienThi() const {
        cout << left << setw(10) << maSV
             << setw(25) << hoTen
             << setw(8) << fixed << setprecision(2) << diemTB << endl;
    }
};

class DanhSachSinhVien {
private:
    list<SinhVien> danhSach;

public:

    void docTuTep(const string& tenTep) {
        ifstream file(tenTep);
        if (!file.is_open()) {
            cout << "Khong the mo tep " << tenTep << endl;
            return;
        }

        danhSach.clear();
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            // format in file if this maSV|hoTen|diemTB
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);

            if (pos1 != string::npos && pos2 != string::npos) {
                string maSV = line.substr(0, pos1);
                string hoTen = line.substr(pos1 + 1, pos2 - pos1 - 1);
                float diemTB = stof(line.substr(pos2 + 1));

                danhSach.push_back(SinhVien(maSV, hoTen, diemTB));
            }
        }
        file.close();
        cout << "Da doc " << danhSach.size() << " sinh vien tu tep." << endl;
    }


    void hienThiDanhSach() const {
        if (danhSach.empty()) {
            cout << "Danh sach sinh vien rong!" << endl;
            return;
        }

        cout << "\n=== DANH SACH SINH VIEN ===" << endl;
        cout << left << setw(10) << "Ma SV"
             << setw(25) << "Ho Ten"
             << setw(8) << "Diem TB" << endl;
        cout << string(43, '-') << endl;

        for (const auto& sv : danhSach) {
            sv.hienThi();
        }
        cout << "Tong so sinh vien: " << danhSach.size() << endl;
    }

    void ghiRaTep(const string& tenTep) const {
        ofstream file(tenTep);
        if (!file.is_open()) {
            cout << "Khong the tao tep " << tenTep << endl;
            return;
        }

        for (const auto& sv : danhSach) {
            file << sv.getMaSV() << "|" << sv.getHoTen() << "|" << sv.getDiemTB() << endl;
        }
        file.close();
        cout << "Da ghi " << danhSach.size() << " sinh vien ra tep " << tenTep << endl;
    }


    void timSinhVien(const string& ten) const {
        bool timThay = false;
        cout << "\n=== KET QUA TIM KIEM ===" << endl;
        cout << left << setw(10) << "Ma SV"
             << setw(25) << "Ho Ten"
             << setw(8) << "Diem TB" << endl;
        cout << string(43, '-') << endl;

        for (const auto& sv : danhSach) {
            if (sv.getHoTen().find(ten) != string::npos) {
                sv.hienThi();
                timThay = true;
            }
        }

        if (!timThay) {
            cout << "Khong tim thay sinh vien co ten chua \"" << ten << "\"" << endl;
        }
    }

    void xoaSinhVien(const string& ten) {
        int soLuongXoa = 0;
        auto it = danhSach.begin();

        while (it != danhSach.end()) {
            if (it->getHoTen().find(ten) != string::npos) {
                cout << "Da xoa sinh vien: ";
                it->hienThi();
                it = danhSach.erase(it);
                soLuongXoa++;
            } else {
                ++it;
            }
        }

        if (soLuongXoa == 0) {
            cout << "Khong tim thay sinh vien co ten chua \"" << ten << "\" de xoa." << endl;
        } else {
            cout << "Da xoa " << soLuongXoa << " sinh vien." << endl;
        }
    }

    void sapXepTheoDiem() {
        danhSach.sort([](const SinhVien& a, const SinhVien& b) {
            return a.getDiemTB() > b.getDiemTB();
        });
        cout << "Da sap xep danh sach theo diem trung binh giam dan." << endl;
    }


    void themSinhVienSapXep(const SinhVien& svMoi) {

        auto it = danhSach.begin();
        while (it != danhSach.end() && it->getDiemTB() >= svMoi.getDiemTB()) {
            ++it;
        }
        danhSach.insert(it, svMoi);
        cout << "Da them sinh vien vao danh sach sap xep." << endl;
    }


    void themSinhVien() {
        SinhVien svMoi;
        cout << "\n=== THEM SINH VIEN MOI ===" << endl;
        svMoi.nhap();
        danhSach.push_back(svMoi);
        cout << "Da them sinh vien thanh cong!" << endl;
    }


    bool isEmpty() const {
        return danhSach.empty();
    }
};


void hienThiMenu() {
    cout << "\n========== MENU QUAN LY SINH VIEN ==========" << endl;
    cout << "1. Doc danh sach sinh vien tu tep" << endl;
    cout << "2. Hien thi danh sach sinh vien" << endl;
    cout << "3. Ghi danh sach sinh vien ra tep" << endl;
    cout << "4. Tim sinh vien theo ten" << endl;
    cout << "5. Xoa sinh vien theo ten" << endl;
    cout << "6. Sap xep danh sach theo diem TB giam dan" << endl;
    cout << "7. Them sinh vien vao danh sach sap xep" << endl;
    cout << "8. Them sinh vien moi" << endl;
    cout << "0. Thoat chuong trinh" << endl;
    cout << "===========================================" << endl;
    cout << "Lua chon cua ban: ";
}


int main() {
    DanhSachSinhVien ds;
    int luaChon;
    string tenTep, tenSinhVien;

    do {
        hienThiMenu();
        cin >> luaChon;
        cin.ignore();

        switch (luaChon) {
            case 1: {
                cout << "Nhap ten tep can doc: ";
                getline(cin, tenTep);
                ds.docTuTep(tenTep);
                break;
            }
            case 2: {
                ds.hienThiDanhSach();
                break;
            }
            case 3: {
                if (ds.isEmpty()) {
                    cout << "Danh sach rong! Khong co gi de ghi." << endl;
                    break;
                }
                cout << "Nhap ten tep de ghi: ";
                getline(cin, tenTep);
                ds.ghiRaTep(tenTep);
                break;
            }
            case 4: {
                cout << "Nhap ten sinh vien can tim: ";
                getline(cin, tenSinhVien);
                ds.timSinhVien(tenSinhVien);
                break;
            }
            case 5: {
                cout << "Nhap ten sinh vien can xoa: ";
                getline(cin, tenSinhVien);
                ds.xoaSinhVien(tenSinhVien);
                break;
            }
            case 6: {
                if (ds.isEmpty()) {
                    cout << "Danh sach rong! Khong co gi de sap xep." << endl;
                    break;
                }
                ds.sapXepTheoDiem();
                break;
            }
            case 7: {
                SinhVien svMoi;
                cout << "\n=== THEM SINH VIEN VAO DANH SACH SAP XEP ===" << endl;
                svMoi.nhap();
                ds.themSinhVienSapXep(svMoi);
                break;
            }
            case 8: {
                ds.themSinhVien();
                break;
            }
            case 0: {
                cout << "Cam on ban da sử dụng chuong trinh!" << endl;
                break;
            }
            default: {
                cout << "Lua chon khong hop le! Vui long chon lai." << endl;
                break;
            }
        }

        if (luaChon != 0) {
            cout << "\nNhan Enter de tiep tuc...";
            cin.get();
            system("cls");
        }

    } while (luaChon != 0);

    return 0;
}
