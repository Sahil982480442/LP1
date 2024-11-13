#include<iostream>
#include<limits.h>
#include<vector>
using namespace std;

void bestFit(vector<int> blockSizes,vector<int> processSizes){
    int m = blockSizes.size();
    int n = processSizes.size();
    vector<int> allocation(n, - 1);
    for(int i = 0;i<n;i++){
        int bestIdx = -1;
        for(int j = 0;j<m;j++){
            if(blockSizes[j]>=processSizes[i]){
                if(bestIdx == -1 || blockSizes[j]<blockSizes[bestIdx]){     // blockSizes[j]<blockSizes[bestIdx]
                    bestIdx = j;
                }
            }
        }
        if(bestIdx!=-1){
            allocation[i] = bestIdx;
            blockSizes[bestIdx] -= processSizes[i];
        }
    }
    cout<<"----------------------------------------------------"<<endl;
    cout<<"ProcessNo.\tProcess Size\tBlock No.\n";
    for(int i = 0;i<n;i++){
        cout<<i+1<<"\t\t"<<processSizes[i]<<"\t\t";
        if(allocation[i]!=-1){
            cout<<allocation[i]+1<<endl;
        }
        else{
            cout<<"Not allocated\n";
        }
    }
}


void worstFit(vector<int> blockSizes,vector<int> processSizes){
    int m = blockSizes.size();
    int n = processSizes.size();

    vector<int> allocation(n, - 1);

    for(int i = 0;i<n;i++){
        int worstIdx = -1;
        for(int j = 0;j<m;j++){
            if(blockSizes[j]>=processSizes[i]){
                if(worstIdx == -1 || blockSizes[j]>blockSizes[worstIdx]){        // >
                    worstIdx = j;
                }
            }
        }
        if(worstIdx!=-1){
            allocation[i] = worstIdx;
            blockSizes[worstIdx] -= processSizes[i];
        }
    }
    cout<<"----------------------------------------------------"<<endl;
    cout<<"ProcessNo.\tProcess Size\tBlock No.\n";
    for(int i = 0;i<n;i++){
        cout<<i+1<<"\t\t"<<processSizes[i]<<"\t\t";
        if(allocation[i]!=-1){
            cout<<allocation[i]+1<<endl;
        }
        else{
            cout<<"Not allocated\n";
        }
    }
}

void firstFit(vector<int> blockSizes,vector<int> processSizes){
    int m = blockSizes.size();
    int n = processSizes.size();

    vector<int> allocation(n, - 1);

    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            if(blockSizes[j]>=processSizes[i]){
                allocation[i] = j;
                blockSizes[j]-=processSizes[i];
                break;                                  // break
            }
        }
    }
    cout<<"----------------------------------------------------"<<endl;
    cout<<"ProcessNo.\tProcess Size\tBlock No.\n";
    for(int i = 0;i<n;i++){
        cout<<i+1<<"\t\t"<<processSizes[i]<<"\t\t";
        if(allocation[i]!=-1){
            cout<<allocation[i]+1<<endl;
        }
        else{
            cout<<"Not allocated\n";
        }
    }
}

void nextFit(vector<int> blockSizes,vector<int> processSizes){
    int m = blockSizes.size();
    int n = processSizes.size();
    vector<int> allocation(n,-1);
    int lastAllocatedBlock = 0;
    for(int i = 0;i<n;i++){
        int startIdx = lastAllocatedBlock;
        while(true){
            if(blockSizes[lastAllocatedBlock]>=processSizes[i]){
                allocation[i] = lastAllocatedBlock;
                blockSizes[lastAllocatedBlock]-=processSizes[i];
                break;
            }
            lastAllocatedBlock = (lastAllocatedBlock+1)%m;    //
            if(lastAllocatedBlock == startIdx){
                break;
            }
        }
    }
    cout<<"----------------------------------------------------"<<endl;
    cout << "ProcessNo.\tProcess Size\tBlock No.\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t\t" << processSizes[i] << "\t\t";
        if (allocation[i] != -1) {
            cout << allocation[i] + 1 << endl; // Print block index as 1-based
        } else {
            cout << "Not allocated\n";
        }
    }
}


int main() {
    vector<int> blockSizes = {100, 500, 200, 300, 600};
    vector<int> processSizes = {212, 417, 112, 426};
    bestFit(blockSizes, processSizes);
    worstFit(blockSizes, processSizes);
    firstFit(blockSizes, processSizes);
    nextFit(blockSizes, processSizes);
    return 0;
}