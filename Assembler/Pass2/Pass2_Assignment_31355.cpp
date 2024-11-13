#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream ic("ic.txt"), st("symbol_Table.txt"), lt("Literal_table.txt");
    ofstream fout("output.txt");

    if (!ic.is_open() || !st.is_open() || !lt.is_open() || !fout.is_open()) {
        cerr << "Error opening one or more files!" << endl;
        return 1;
    }

    unordered_map<int, string> symbolTable;
    unordered_map<int, string> literalTable;

    int sno;
    string sname, saddr;
    while (st >> sno >> sname >> saddr)
    {
        symbolTable[sno] = saddr;
    }

    int lno;
    string lname, laddr;
    while (lt >> lno >> lname >> laddr)
    {
        literalTable[lno] = laddr;
    }

    string lc, instruction, op1, op2;
    while (ic >> lc >> instruction >> op1 >> op2)
    {
        if (lc == "---") continue;

        string oOpcode = instruction.substr(4, 2);
        string oOp1 = "0";
        string oOp2 = "000";

        if (instruction.substr(1, 2) == "DL")
        {
            if (instruction[5] == '1')
            {
                oOpcode = "00";
                oOp1 = "0";
                oOp2[2] = op1[3];
            } 
            else if (instruction[5] == '2')
            {
                int spaces = op1[3] - '0';    //////// char to int
                for (int i = 1; i < spaces; i++)
                {
                    fout << lc << "  \t" << "+" << "\t" << "00" << "\t" << "0" << "\t" << "000" << endl;
                }
                oOpcode = "00";
                oOp1 = "0";
            }
        }
        else
        {
            if (op1 != "NAN")
            {
                oOp1 = op1[1];
            }

            if (op2[1] == 'L')
            {
                int idx = op2[4] - '0';
                oOp2 = literalTable[idx];
            }
            else if (op2[1] == 'S')
            {
                int idx = op2[4] - '0';
                oOp2 = symbolTable[idx];
            }
        }

        fout << lc << "  \t" << "+" << "\t" << oOpcode << "\t" << oOp1 << "\t" << oOp2 << endl;
    }

    ic.close();
    st.close();
    lt.close();
    fout.close();

    return 0;
}