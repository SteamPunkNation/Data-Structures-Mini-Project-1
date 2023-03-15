#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;
class HeapBuilder {
public:
int o=0;
void enter()
{
  int n;
  cin>>n;
  int data[n];
  for (int i=0; i<n;i++)
    cin>>data[i];
  buildHeap(data, n);
}
void swap(int *num, int *smallest)
{
    int tmp = *num;
      *num = *smallest;
      *smallest = tmp;
}
void siftDown(int arr[], int N, int i)
{
    int smallest = i;
    int left = 2 * i + 1; 
    int right = 2 * i + 2; 
  
    if (left < N && arr[left] < arr[smallest])
        smallest = left;
  
   
    if (right < N && arr[right] < arr[smallest])
        smallest = right;
  
    
    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        cout<<i<<" "<<smallest<<std::endl;
        o++;
        siftDown(arr, N, smallest);
    }
}
void buildHeap(int arr[], int N)
{
    int startIdx = (N / 2) - 1;
    for (int i = startIdx; i >= 0; i--) {
        siftDown(arr, N, i);
    }
}
void printO()
{
  cout<<o;
}
};
int main() {
std::ios_base::sync_with_stdio(false);
HeapBuilder heap_builder;
heap_builder.enter();
heap_builder.printO();
return 0;
}
