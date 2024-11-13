#include <bits/stdc++.h>
using namespace std;

struct OPtab
{
    string opcode;
    string mclass;
    string mnemonic;
};

struct OPtab optab[18] = {
    {"STOP", "IS", "00"},
    {"ADD", "IS", "01"},
    {"SUB", "IS", "02"},
    {"MULT", "IS", "03"},
    {"MOVER", "IS", "04"},
    {"MOVEM", "IS", "05"},
    {"COMP", "IS", "06"},
    {"BC", "IS", "07"},
    {"DIV", "IS", "08"},
    {"READ", "IS", "09"},
    {"PRINT", "IS", "10"},
    {"START", "AD", "01"},
    {"END", "AD", "02"},
    {"ORIGIN", "AD", "03"},
    {"EQU", "AD", "04"},
    {"LTORG", "AD", "05"},
    {"DC", "DL", "01"},
    {"DS", "DL", "02"}
};

int getOP(string s)
{
    for (int i = 0; i < 18; ++i)
    {
        if (optab[i].opcode == s)
            return i;
    }
    return -1;
}

int getRegID(string s)
{
    if (s == "AREG")
        return 1;
    else if (s == "BREG")
        return 2;
    else if (s == "CREG")
        return 3;
    else if (s == "DREG")
        return 4;
    else
        return (-1);
}

int getConditionCode(string s)
{
    if (s == "LT")
        return 1;
    else if (s == "LE")
        return 2;
    else if (s == "EQ")
        return 3;
    else if (s == "GT")
        return 4;
    else if (s == "GE")
        return 5;
    else if (s == "ANY")
        return 6;
    else
        return (-1);
}

struct symTable
{
    int no;
    string sname;
    string addr;
};

struct symTable ST[10];

bool presentST(string s)
{
    for (int i = 0; i < 10; ++i)
    {
        if (ST[i].sname == s)
            return true;
    }
    return false;
}

int getSymID(string s)
{
    for (int i = 0; i < 10; ++i)
    {
        if (ST[i].sname == s)
            return i;
    }
    return (-1);
}

struct litTable
{
    int no;
    string lname;
    string addr;
};

struct litTable LT[10];

bool presentLT(string s)
{
    for (int i = 0; i < 10; ++i)
    {
        if (LT[i].lname == s)
            return true;
    }
    return false;
}

int getLitID(string s)
{
    for (int i = 0; i < 10; ++i)
    {
        if (LT[i].lname == s)
            return i;
    }
    return (-1);
}

struct poolTable
{
    int no;
    string lno;
};

struct poolTable PT[10];

int main()
{
    ifstream fin;
    fin.open("input.txt");

    ofstream ic, st, lt, pt;
    
    ic.open("ic.txt");
    st.open("sym_table.txt");
    lt.open("lit_table.txt");
    pt.open("pool_table.txt");
    string label, opcode, op1, op2;

    int scnt = 0, lcnt = 0, nlcnt = 0, pcnt = 0, LC = 0;

    cout << "\n -- ASSEMBLER PASS-1 OUTPUT --" << endl;
    cout << "\n <LABEL\tOPCODE\tOP1\tOP2\tLC\tINTERMEDIATE CODE>" << endl;

    while (!fin.eof())                                              ////////////////////////////// (!fin.eof())
    {
        fin >> label >> opcode >> op1 >> op2; 
        int id;
        string IC, lc; 

        id = getOP(opcode); 
        IC = "(" + optab[id].mclass + "," + optab[id].mnemonic + ") ";

        if (opcode == "START")
        {
            lc = "---";
            if (op1 != "NAN")
            {
                LC = stoi(op1);                                         /// Int LC
                IC += "(C," + op1 + ") NAN";
            }
        }

        if (opcode == "EQU")
        {
            lc = "---";
            IC += " NAN NAN";                               ///// Not NAN NAN instead (S,02)    ////
            if (presentST(label))                                               ////// Two cases of already exist or not
            {
                ST[getSymID(label)].addr = ST[getSymID(op1)].addr;
            }
            else
            {
                ST[scnt].no = scnt + 1;
                ST[scnt].sname = label;
                ST[scnt].addr = ST[getSymID(op1)].addr;
                scnt++;
            }
        }

        else if (label != "NAN")                        ///// IMP as label address assignment
        {
            if (presentST(label))
            {
                ST[getSymID(label)].addr = to_string(LC);   // Current LC assignment
            }
            else
            {
                ST[scnt].no = scnt + 1;
                ST[scnt].sname = label;
                ST[scnt].addr = to_string(LC);
                scnt++;
            }
        }

        if (opcode == "ORIGIN")             ////////////////////////////////////////////////////////////////////////////////////////
        {
            string token1, token2;
            char op;
            stringstream ss(op1);
            size_t found = op1.find('+');
            if (found != string::npos)
                op = '+';
            else
                op = '-';
            getline(ss, token1, op);
            getline(ss, token2, op);
            lc = "---";
            if (op == '+')
            {
                LC = stoi(ST[getSymID(token1)].addr) + stoi(token2);                /// LC is changing
                IC += "(S,0" + to_string(ST[getSymID(token1)].no) + ")+" + token2 + " NAN";
            }
            else
            {
                LC = stoi(ST[getSymID(token1)].addr) - stoi(token2);
                IC += "(S,0" + to_string(ST[getSymID(token1)].no) + ")-" + token2 + " NAN";
            }
        }



        if (opcode == "LTORG")
        {
            IC += " NAN NAN";
            cout << " " << label << "\t" << opcode << "\t" << op1 << "\t" << op2 << "\t";
            cout << "---" << "\t" << IC << endl;
            ic << "---" << "\t" << IC << endl;
            for (int i = lcnt - nlcnt; i < lcnt; ++i)
            {
                lc = to_string(LC);
                string literalValue = LT[i].lname.substr(2, 1); // Extracting value from ='5'
                IC = "(DL,01) (C," + literalValue + ") NAN";
                LT[i].addr = to_string(LC);
                LC++;                       /////////////////
                                   
                cout << "\t\t\t\t" << lc << "\t" << IC << endl;
                ic << lc << "\t" << IC << endl;
            }
            PT[pcnt].lno = "#" + to_string(LT[lcnt - nlcnt].no);            // pool table
            PT[pcnt].no = pcnt + 1;
            pcnt++;
            nlcnt = 0; /////////////////
            continue;   // ?????????????????????????????????
        }



        if (opcode == "END")
        {
            lc = "---";
            IC += " NAN NAN";
            cout << " " << label << "\t" << opcode << "\t" << op1 << "\t" << op2 << "\t" << lc << "\t" << IC << endl;
            ic << lc << "\t" << IC << endl;
            if (nlcnt)
            {
                for (int i = lcnt - nlcnt; i < lcnt; ++i)
                {
                    lc = to_string(LC);
                    IC = "(DL,01) (C,";
                    string c(1, LT[i].lname[2]);
                    IC += c + ") NAN";
                    LT[i].addr = to_string(LC);
                    LC++;
                    cout << "\t\t\t\t" << lc << "\t" << IC << endl;
                    ic << lc << "\t" << IC << endl;
                }
                
                PT[pcnt].lno = "#" + to_string(LT[lcnt - nlcnt].no);
                PT[pcnt].no = pcnt + 1;
                pcnt++;
            }
            break;                              // ????????????????????????
        }

        if (opcode == "DC" || opcode == "DS")
        {
            lc = to_string(LC);
            if (opcode == "DS")
            {
                IC += "(C," + op1 + ") NAN";
                LC += stoi(op1);
            }
            else
            {
                string c(1, op1[1]);
                IC += "(C," + c + ")";
                LC++;
            }
        }

        if (opcode != "START" && opcode != "END" && opcode != "ORIGIN" && opcode != "EQU" && opcode != "LTORG" && opcode != "DC" && opcode != "DS")
        {
            if (op2 == "NAN")
            {
                if (op1 == "NAN")       // STOP
                {
                    lc = to_string(LC);                 // current LC value
                    LC++;                       //as imerative
                    IC += " NAN NAN";
                }
                else        ////////////////////////////////////////////////  ?????????????????
                {
                    if (presentST(op1))
                    {
                        IC += "(S,0" + to_string(ST[getSymID(op1)].no) + ")";
                        lc = to_string(LC);
                        LC++;
                    }
                    else
                    {
                        ST[scnt].no = scnt + 1;
                        ST[scnt].sname = op1;
                        scnt++;
                        IC += "(S,0" + to_string(ST[getSymID(op1)].no) + ")";
                        lc = to_string(LC);
                        LC++;
                    }
                }
            }
            else
            {
                if (opcode == "BC")
                    IC += "(" + to_string(getConditionCode(op1)) + ") ";
                else
                    IC += "(" + to_string(getRegID(op1)) + ") ";

                if (op2[0] == '=') 
                {
                    LT[lcnt].no = lcnt + 1;
                    LT[lcnt].lname = op2;
                    lcnt++;
                    nlcnt++;                                    /////////??????????????
                    IC += "(L,0" + to_string(LT[getLitID(op2)].no) + ")";
                }
                else 
                {
                    if (presentST(op2))
                    {
                        IC += "(S,0" + to_string(ST[getSymID(op2)].no) + ")";
                    }
                    else
                    {
                        ST[scnt].no = scnt + 1;
                        ST[scnt].sname = op2;
                        scnt++;
                        IC += "(S,0" + to_string(ST[getSymID(op2)].no) + ")";
                    }
                }
                lc = to_string(LC);
                LC++;
            }
        }

        cout << " " << label << "\t" << opcode << "\t" << op1 << "\t" << op2 << "\t" << lc << "\t" << IC << endl;
        ic << lc << "\t" << IC << endl;
    }

    cout << "\n----------------------------------------------------------------" << endl;
    cout << " -- SYMBOL TABLE --" << endl;
    cout << "\n <NO.\tSYMBOL\tADDRESS>" << endl;
    for (int i = 0; i < scnt; ++i)
    {
        cout << " " << ST[i].no << "\t " << ST[i].sname << "\t " << ST[i].addr << endl;
        st << ST[i].no << "\t " << ST[i].sname << "\t " << ST[i].addr << endl;
    }

    cout << "\n----------------------------------------------------------------" << endl;
    cout << " -- LITERAL TABLE --" << endl;
    cout << "\n <NO.\tLITERAL\tADDRESS>" << endl;
    for (int i = 0; i < lcnt; ++i)
    {
        cout << " " << LT[i].no << "\t " << LT[i].lname << "\t " << LT[i].addr << endl;
        lt << LT[i].no << "\t " << LT[i].lname << "\t " << LT[i].addr << endl;
    }

    cout << "\n----------------------------------------------------------------" << endl;
    cout << " -- POOL TABLE --" << endl;
    cout << "\n <NO.\tLITERAL_NO.>" << endl;
    for (int i = 0; i < pcnt; ++i)
    {
        cout << " " << PT[i].no << "\t " << PT[i].lno << endl;
        pt << PT[i].no << "\t " << PT[i].lno << endl;
    }

    return 0;
}
