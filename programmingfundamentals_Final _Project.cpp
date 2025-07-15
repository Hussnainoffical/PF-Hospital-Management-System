#include<iostream>
#include<fstream>
#include<string>
using namespace std;

const string APPOINT_FILE = "online patient appointment.txt";

bool isValidTxtFile(const string& filename) {
    return filename.size() >= 4 && filename.substr(filename.size() - 4) == ".txt";
}

bool getPatientData(string &name, int &age, string &disease, string &admissionDate, string &dischargeDate) {
    cin.ignore();
    cout << "Enter patient name: ";
    getline(cin, name);
    if (name.empty()) { cout << "Name cannot be empty.\n"; return false; }
    cout << "Enter patient age: ";
    cin >> age;
    if (age <= 0 || age > 120) { cout << "Invalid age.\n"; return false; }
    cin.ignore();
    cout << "Enter patient disease: ";
    getline(cin, disease);
    if (disease.empty()) { cout << "Disease cannot be empty.\n"; return false; }
    cout << "Enter patient Date of admission: ";
    getline(cin, admissionDate);
    if (admissionDate.empty()) { cout << "Admission date cannot be empty.\n"; return false; }
    cout << "Enter patient Date of Discharge: ";
    getline(cin, dischargeDate);
    if (dischargeDate.empty()) { cout << "Discharge date cannot be empty.\n"; return false; }
    return true;
}

void updatedata() {
    cout << "What's your file name: " << endl;
    string filename;
    cin >> filename;
    if (!isValidTxtFile(filename)) {
        cout << "File name must end with .txt\n";
        return;
    }
    ifstream file(filename.c_str());
    if (file.is_open()) {
        file.close();
        cout << "File exists. Write new data" << endl;
        cout << "Warning: This will overwrite existing data. Continue? (y/n): ";
        char confirm;
        cin >> confirm;
        if (confirm != 'y' && confirm != 'Y') return;
        string patient_name, disease, admissiondate, dateofout;
        int age;
        if (!getPatientData(patient_name, age, disease, admissiondate, dateofout)) return;
        cout << "Patient Name   : " << patient_name << endl;
        cout << "Patient Age    : " << age << endl;
        cout << "Patient Disease: " << disease << endl;
        cout << "Admission Date : " << admissiondate << endl;
        cout << "Discharge Date : " << dateofout << endl;
        ofstream outfile(filename.c_str());
        if (!outfile.is_open()) {
            cout << "Error opening file for writing.\n";
            return;
        }
        outfile << "Patient Name   : " << patient_name << endl;
        outfile << "Patient Age    : " << age << endl;
        outfile << "Patient Disease: " << disease << endl;
        outfile << "Admission Date : " << admissiondate << endl;
        outfile << "Discharge Date : " << dateofout << endl;
        outfile << endl;
        outfile.close();
    } else {
        cout << "File does not exist." << endl;
    }
}

void newrecord() {
    string patient_name, disease, admissiondate, dateofout;
    int age;
    if (!getPatientData(patient_name, age, disease, admissiondate, dateofout)) return;
    cout << "Patient Name   : " << patient_name << endl;
    cout << "Patient Age    : " << age << endl;
    cout << "Patient Disease: " << disease << endl;
    cout << "Admission Date : " << admissiondate << endl;
    cout << "Discharge Date : " << dateofout << endl;
    string filename;
    bool filename_exists = true;
    while (filename_exists) {
        cout << "Enter your unique file name (include .txt at the end): " << endl;
        cin >> filename;
        if (!isValidTxtFile(filename)) {
            cout << "File name must end with .txt\n";
            continue;
        }
        ifstream file(filename.c_str());
        if (file.is_open()) {
            cout << "File name already exists. Please choose another file name." << endl;
            file.close();
        } else {
            ofstream outfile(filename.c_str());
            if (!outfile.is_open()) {
                cout << "Error opening file for writing.\n";
                char retry;
                cout << "Try again? (y/n): ";
                cin >> retry;
                if (retry == 'y' || retry == 'Y') continue;
                else return;
            }
            outfile << "Patient Name   : " << patient_name << endl;
            outfile << "Patient Age    : " << age << endl;
            outfile << "Patient Disease: " << disease << endl;
            outfile << "Admission Date : " << admissiondate << endl;
            outfile << "Discharge Date : " << dateofout << endl;
            outfile << endl;
            outfile.close();
            filename_exists = false;
        }
    }
}

void viewrecord() {
    cout << "What's your file name: " << endl;
    string filename;
    cin >> filename;
    if (!isValidTxtFile(filename)) {
        cout << "File name must end with .txt\n";
        return;
    }
    ifstream file(filename.c_str());
    if (file.is_open()) {
        string line;
        cout << "File exists. Here are its contents:" << endl;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "File does not exist." << endl;
    }
}

int main() {
    fstream myfile;
    int ct = 0;
    myfile.open(APPOINT_FILE.c_str(), ios::app | ios::out | ios::in);
    ifstream myreadfile(APPOINT_FILE.c_str());
    int val;
    string s;
    string time;
    if (myreadfile.is_open()) {
        while (getline(myreadfile, time)) {
            ct++;
        }
        val = ct;
    } else {
        val = 0;
    }
    int time_table;
    string day;
    cout << "Press 1 to log-in as doctor: " << endl;
    cout << "Press 2 to log-in as patient" << endl;
    int choice;
    if (!(cin >> choice)) {
        cout << "Invalid input. Exiting.\n";
        return 1;
    }
    cin.ignore();
    switch (choice) {
    case 1:
        cout << "Logged in as doctor" << endl;
        cout << "Press 1 to update appointment times " << endl;
        cout << "Press 2 to enter daily income to calculate salary" << endl;
        if (!(cin >> time_table)) {
            cout << "Invalid input. Exiting.\n";
            return 1;
        }
        cin.ignore();
        switch (time_table) {
        case 1: {
            int i = 1;
            while (i != 0) {
                myfile << (ct + 1) << ")";
                cout << "Which day is the doctor available?" << endl;
                cin >> day;
                day = "March-" + day + "\t";
                cout << "Which time is the doctor available?" << endl;
                cin >> time;
                time = time + "pm\n";
                myfile << day << time;
                cout << "Do you want to enter another day?\nPress 0 to exit appointment schedule\nPress any other numeric value to continue entering more slots\n";
                if (!(cin >> i)) {
                    cout << "Invalid input. Exiting.\n";
                    return 1;
                }
                cin.ignore();
                val++;
            }
            myfile.close();
            break;
        }
        case 2: {
            float dailyEarning, totalEarning = 0;
            cout << "Please enter the daily earning of the doctor: ";
            if (!(cin >> dailyEarning)) {
                cout << "Invalid input. Exiting.\n";
                return 1;
            }
            for (int i = 1; i <= 30; i++) {
                totalEarning += dailyEarning;
            }
            cout << "The total earning of the doctor in this month is: " << totalEarning << endl;
            break;
        }
        default:
            cout << "Invalid option.\n";
        }
        break;
    case 2:
        cout << "Logged in as patient\nPress 1 For New patient profile \nPress 2 Already Profile exists \nPress 3 for update data \nPress 4 for Choose any appointment slot number from following available times\n";
        int press;
        if (!(cin >> press)) {
            cout << "Invalid input. Exiting.\n";
            return 1;
        }
        cin.ignore();
        if (press == 1) {
            newrecord();
        } else if (press == 2) {
            viewrecord();
        } else if (press == 3) {
            updatedata();
        } else if (press == 4) {
            string mytext;
            int n = 0;
            string appoint[50];
            ifstream myreadfile(APPOINT_FILE.c_str());
            for (int i = 0; getline(myreadfile, appoint[i]); i++) {
                cout << appoint[i] << endl;
                n++;
            }
            string choice;
            cin >> choice;
            cin.ignore();
            bool bl = false;
            for (int i = 0; i < n; i++) {
                size_t pos = appoint[i].find(")");
                if (pos != string::npos) {
                    string slotnum = appoint[i].substr(0, pos);
                    string slotnum_nospace = "";
                    for (int k = 0; k < slotnum.length(); k++) {
                        if (slotnum[k] != ' ') slotnum_nospace += slotnum[k];
                    }
                    if (slotnum_nospace == choice) {
                        appoint[i] += " (BOOKED)";
                        bl = true;
                    }
                }
            }
            if (bl) {
                ofstream outFile(APPOINT_FILE.c_str());
                for (int i = 0; i < n; i++) {
                    outFile << appoint[i] << endl;
                }
                cout << "Appointment slot no. " << choice << " Booked.";
            } else {
                cout << "Not a slot";
            }
        } else {
            cout << "There is no other option " << endl;
        }
        break;
    default:
        cout << "Invalid option.\n";
    }
    return 0;
}
