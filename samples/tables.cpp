#include "tables.h"
#include "Postfix.h"

template<typename T>
void menu(T* table, array_un_table<string, Polynom>* table_1, list_un_table<string, Polynom>* table_2, AVL_tree_table<string, Polynom>* table_3, array_table<string, Polynom>* table_4, first_hash_table* table_5, second_hash_table* table_6) {
    while (true) {
        cout << "select the desired operation:" << endl;
        cout << "1 - insert a polynomial into a table" << endl;
        cout << "2 - remove polynomial from table" << endl;
        cout << "3 - find a polynomial in a table" << endl;
        cout << "4 - select operations with polynomial" << endl;
        cout << "5 - calculate expression with polynomials" << endl;
        cout << "6 - display the active table on the screen" << endl;
        cout << "7 - back" << endl;
        int select_1;
        cin >> select_1;
        if (select_1 == 7)
            return;
        switch (select_1)
        {
        default:
            break;
        case 1:
        {
            cout << "enter the name of the polynomial (example: pol1):" << endl;
            string tmp_1;
            cin >> tmp_1;
            cout << "enter polynomial (example: 3.6x^2yz-2z+1):" << endl;
            string tmp_3;
            cin >> tmp_3;
            Polynom tmp_2(tmp_3);
            table_1->Insert(tmp_1, tmp_2);
            table_2->Insert(tmp_1, tmp_2);
            table_3->Insert(tmp_1, tmp_2);
            table_4->Insert(tmp_1, tmp_2);
            table_5->Insert(tmp_1, tmp_2);
            table_6->Insert(tmp_1, tmp_2);
            break;
        }
        case 2:
        {
            cout << "enter the name of the polynomial (example: pol1):" << endl;
            string tmp_1;
            cin >> tmp_1;
            table_1->Delete(tmp_1);
            table_2->Delete(tmp_1);
            table_3->Delete(tmp_1);
            table_4->Delete(tmp_1);
            table_5->Delete(tmp_1);
            table_6->Delete(tmp_1);
            break;
        }
        case 3:
        {
            cout << "enter the name of the polynomial (example: pol1):" << endl;
            string tmp_1;
            cin >> tmp_1;
            auto tmp_2 = table->Find(tmp_1);
            if (tmp_2 == nullptr) {
                cout << "polynomial not found" << endl;
            }
            else {
                cout << *(tmp_2) << endl;
            }
            break;
        }
        case 4:
        {
            while (true) {
                cout << "1 - calculate the value of a polynomial at a point" << endl;
                cout << "2 - multiply a polynomial by a constant" << endl;
                cout << "3 - back" << endl;
                int select_2;
                cin >> select_2;
                if (select_2 == 3)
                    break;
                switch (select_2)
                {
                default:
                    break;
                case 1:
                {
                    cout << "enter the name of the polynomial (example: pol1):" << endl;
                    string tmp_1;
                    cin >> tmp_1;
                    auto tmp_2 = table->Find(tmp_1);
                    if (tmp_2 == nullptr) {
                        cout << "polynomial not found" << endl;
                    }
                    else {
                        cout << "enter the x coordinate of the point (example: 0.0):" << endl;
                        double x;
                        cin >> x;
                        cout << "enter the y coordinate of the point (example: 0.0):" << endl;
                        double y;
                        cin >> y;
                        cout << "enter the z coordinate of the point (example: 0.0):" << endl;
                        double z;
                        cin >> z;
                        cout << "value = " << tmp_2->value(x, y, z) << endl;
                    }
                    break;
                }
                case 2:
                {
                    cout << "enter the name of the polynomial (example: pol1):" << endl;
                    string tmp_1;
                    cin >> tmp_1;
                    auto tmp_2 = table->Find(tmp_1);
                    if (tmp_2 == nullptr) {
                        cout << "polynomial not found" << endl;
                    }
                    else {
                        cout << "enter a constant (example: 0.0):" << endl;
                        double c;
                        cin >> c;
                        Polynom tmp_3 = (*tmp_2);
                        tmp_3 = tmp_3 * c;
                        cout << "new " << tmp_1 << " = " << tmp_3 << endl;
                        cout << "save this polynomial?" << endl;
                        cout << "1 - yes" << endl;
                        cout << "2 - no" << endl;
                        int select_3;
                        cin >> select_3;
                        if (select_3 == 1) {
                            cout << "change polynomial " << tmp_1 << " ?" << endl;
                            cout << "1 - yes" << endl;
                            cout << "2 - no, create a new polynomial" << endl;
                            cout << "3 - cancel" << endl;
                            int select_4;
                            cin >> select_4;
                            if (select_4 == 3)
                                break;
                            if (select_4 == 1) {
                                (*tmp_2) = (*tmp_2) * c;
                                break;
                            }
                            if (select_4 == 2) {
                                cout << "enter the name of the polynomial (example: pol1):" << endl;
                                string tmp_1;
                                cin >> tmp_1;
                                table_1->Insert(tmp_1, tmp_3);
                                table_2->Insert(tmp_1, tmp_3);
                                table_3->Insert(tmp_1, tmp_3);
                                table_4->Insert(tmp_1, tmp_3);
                                table_5->Insert(tmp_1, tmp_3);
                                table_6->Insert(tmp_1, tmp_3);
                                break;
                            }
                        }
                    }
                    break;
                }
                }
            }
            break;
        }
        case 5:
        {
            cout << "enter polynomial expression (example: 2*(pol1+2)*pol2+3.6*q-const6):" << endl;
            string tmp_1;
            cin >> tmp_1;
            try {
                Postfix tmp_2(tmp_1);
            }
            catch (const exception& ex) {
                cout << ex.what() << endl;
                break;
            }
            Postfix tmp_2(tmp_1);
            string str = tmp_2.GetPostfix();
            int flag = 0;
            Polynom res;
            string tmp_3 = "";
            Stack<Polynom> ST;
            if (str == "") {
                cout << "result = " << res << endl;
                break;
            }
            for (int i = 0; i < str.size(); i++) {
                if (flag)
                    break;
                switch (str[i])
                {
                default:
                {
                    while (str[i] != ' ') {
                        tmp_3.push_back(str[i]);
                        i++;
                    }
                    auto tmp_4 = table->Find(tmp_3);
                    if (tmp_4 == nullptr) {
                        cout << "polynomial not found" << endl;
                        flag = 1;
                    }
                    else {
                        Polynom tmp_5 = *tmp_4;
                        ST.Push(tmp_5);
                        tmp_3 = "";
                    }
                    break;
                }
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                {
                    while (str[i] != ' ') {
                        tmp_3.push_back(str[i]);
                        i++;
                    }
                    Polynom tmp_4(tmp_3);
                    ST.Push(tmp_4);
                    tmp_3 = "";
                    break;
                }
                case '+':
                {
                    Polynom R = ST.Pop();
                    Polynom L = ST.Pop();
                    ST.Push(L + R);
                    break;
                }
                case '*':
                {
                    Polynom R = ST.Pop();
                    Polynom L = ST.Pop();
                    ST.Push(L * R);
                    break;
                }
                case '-':
                {
                    Polynom R = ST.Pop();
                    Polynom L = ST.Pop();
                    ST.Push(L - R);
                    break;
                }
                }
            }
            if (flag)
                break;
            res = ST.Pop();
            cout << "result = " << res << endl;
            cout << "save this polynomial?" << endl;
            cout << "1 - yes" << endl;
            cout << "2 - no" << endl;
            int select_2;
            cin >> select_2;
            if (select_2 == 1) {
                cout << "enter the name of the polynomial (example: pol1):" << endl;
                string tmp_6;
                cin >> tmp_6;
                table_1->Insert(tmp_6, res);
                table_2->Insert(tmp_6, res);
                table_3->Insert(tmp_6, res);
                table_4->Insert(tmp_6, res);
                table_5->Insert(tmp_6, res);
                table_6->Insert(tmp_6, res);
            }
            break;
        }
        case 6:
        {
            cout << *table;
            break;
        }
        }
    }
}

int main()
{
    array_un_table<string, Polynom> table_1;
    list_un_table<string, Polynom> table_2;
    AVL_tree_table<string, Polynom> table_3;
    array_table<string, Polynom> table_4;
    first_hash_table table_5;
    second_hash_table table_6;
    while (true) {
        cout << "select the active table to store polynomials:" << endl;
        cout << "1 - array_un_table" << endl;
        cout << "2 - list_un_table" << endl;
        cout << "3 - AVL_tree_table" << endl;
        cout << "4 - array_table" << endl;
        cout << "5 - first_hash_table" << endl;
        cout << "6 - second_hash_table" << endl;
        cout << "7 - exit" << endl;
        int select;
        cin >> select;
        if (select == 7)
            return(0);
        switch (select)
        {
        default:
            break;
        case 1:
        {
            menu(&table_1, &table_1, &table_2, &table_3, &table_4, &table_5, &table_6);
            break;
        }
        case 2:
        {
            menu(&table_2, &table_1, &table_2, &table_3, &table_4, &table_5, &table_6);
            break;
        }
        case 3:
        {
            menu(&table_3, &table_1, &table_2, &table_3, &table_4, &table_5, &table_6);
            break;
        }
        case 4:
        {
            menu(&table_4, &table_1, &table_2, &table_3, &table_4, &table_5, &table_6);
            break;
        }
        case 5:
        {
            menu(&table_5, &table_1, &table_2, &table_3, &table_4, &table_5, &table_6);
            break;
        }
        case 6:
        {
            menu(&table_6, &table_1, &table_2, &table_3, &table_4, &table_5, &table_6);
            break;
        }
        }
    }
}