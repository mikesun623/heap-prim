/*
 * mcs9203 Assignment 3
 *
 * Student name: wanbo sun
 * Subject code: mcs9203
 * Student number: 4660213
 * Email ID: ws190
 *
 */
 
#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;
#define max_float 10000.0;//the max float
//--------the print founction--------------------------------
void print(int start_node[],int end_node[],float path[],int num_of_vertices, ofstream& ios)
{
    for(int i=0;i<num_of_vertices-1;i++)
    {
        ios<<start_node[i]<<" -> "<<end_node[i]<<" "<<path[i]<<endl;
    }
    

}
//-----------------from here is the heap list----------------------------------
struct node_list{//linked list struct
    float data;
    node_list* next;
};

void initial_node_list(node_list*& head){//initial link list
    head=NULL;
    return;
}
void printnodes(node_list*& head)		// print the linked list
{
    node_list* temp = head;				// do not change the head pointer
    
    while (temp != NULL)
    {
        cout << temp->data << " " ;
        temp = temp->next;
    }
    return;
}

void creat_node_list_add_node(float lenth, node_list*& head)
{
    node_list* new_node_list = new node_list;
    if (new_node_list == NULL)		// could not allocate memory
    {
        cout << "Allocation error occured" << endl;
        return;
    }
    
    
    if (head == NULL)				// linked list is empty - so this will be the first node
    {
        new_node_list->data=lenth;
        new_node_list->next = NULL;
        head = new_node_list;
    }
    
    else{   //if not empty go to the end of the linked list set node in it
        node_list* pointer = head;
        
        while(pointer!=NULL){
        if(pointer->next==NULL)
        {
            new_node_list->data=lenth;
            new_node_list->next = NULL;
            pointer->next=new_node_list;
            break;
        }
            
        pointer=pointer->next;
        
        }
       
    }
    
    
}

void siftup(float heap[],int i,int lenth)//sift up for the mult queue, the order is from large to small
{
    int c=i*2+1;
    
    if(heap[c]>heap[c+1]&&c+1<=lenth)
    {
        c=c+1;
    }
    if(heap[i]>heap[c]&&c<=lenth)
    {
        swap(heap[i],heap[c]);
        if(c*2+1<=lenth)
            siftup(heap,c,lenth);
    }
    else
        return;
}

//use heap make the data in array in order keep the smallest on the top
void heap_sort(float heap[], int len) {
    //make heap
    for (int i = len / 2 - 1; i >= 0; i--)
        siftup(heap, i, len - 1);
    //swap the first node and the last not sort node, and then sift down, till all the nodes sorted
    for (int i = len - 1; i > 0; i--) {
        swap(heap[0], heap[i]);
        siftup(heap, 0, i - 1);
    }
}




void heap(node_list*& head,float **a,int num_of_vertices,ofstream& ios)//use prim to get the mst
{
    
    ios<<"<-------------------result for the list heap-------------------------------->"<<endl;
    
    int nearst[num_of_vertices];//store the nearst node
    float mindist[num_of_vertices];//store the mindist
    float mindist1[num_of_vertices];
    int end_node=1;
    
    int start_node_result[num_of_vertices];//to store the result of node in the array to print
    int end_node_result[num_of_vertices];//to store the result of node in the array to print
    float mini_result[num_of_vertices];//to store the result of path to print
    int counter=0;//the counter of the node array
    int counter_mini=0;
    
    
    
    
    node_list* pointer = head;
    node_list* node = head;
    for(int i=1;i<num_of_vertices;i++)//start from node 1 all nearst set to 1 mindist equal to the frist row
    {
        nearst[i]=1;
        pointer=pointer->next;
        mindist[i]=pointer->data;
        
    }
    
    float** weight_of_path1 = new float* [num_of_vertices];//the array store all the weight of the nodes
    for (int i = 0; i < num_of_vertices; i++)//init the array
        weight_of_path1[i] = new float[num_of_vertices];
    
    
    
    for(int i=0;i<num_of_vertices;i++)//read in all the weight between the nodes store in the array
    {
        for(int j=0;j<num_of_vertices;j++)
        {
            weight_of_path1[i][j]=node->data;
            node=node->next;
            
        }
    }
    

    
    clock_t t; //to work out time
    t = clock();
    
    int start_node=0;
    int mark=0;// a mark to check if the value have been change from the first time sort, to check connect to node one or not
    int first_time_mark=0;
    float total_value_path=0;
    
    
    for(int i=1;i<num_of_vertices;i++)//repeat n-1 times
    {
        float min= max_float;//set min to max
        
        for(int i=1;i<num_of_vertices;i++)// a fake array to find the smallest node
            mindist1[i]=mindist[i];
        
        heap_sort(mindist1,num_of_vertices);//use heap sort to find the smallest node
        
        for(int i=1;i<num_of_vertices;i++)
        {
            if(mindist1[i]>0)
                min=mindist1[i];//find the position of the node
        }
        
        
        for(int j=1;j<num_of_vertices;j++)//find the min node's position
        {
            if(mindist[j]==min)
            {
                start_node=j;
            }
        }
        
        mini_result[counter_mini]=min;
        counter_mini++;
        
        
        if(first_time_mark==0)//the first time out put 1 to the start node
        {
            start_node_result[counter]=1;
            end_node_result[counter]=start_node+1;
            counter++;
            first_time_mark=1;
        }
        
        
        total_value_path+=min;
        mindist[start_node]=-1;//the node already selected drop it
        
        for(int j=1;j<num_of_vertices;j++)// to find if there's new node connected to the last picked node less than the value in mindist
        {
            
            if(weight_of_path1[j][start_node]<mindist[j])
            {
                mindist[j]=weight_of_path1[j][start_node];// put new smallest value in the minist
                end_node=j+1;
                mark=1;//it is not the node connected to node one
                
            }
            
        }
        if(mark==1&&start_node+1!=end_node)//if node connect to the node one, the value have been changed form the first time sort, it will be a new node
        {
            start_node_result[counter]=start_node+1;
            end_node_result[counter]=end_node;
            counter++;
        }
        if(mark==0&&start_node+1!=end_node)//if connect to node one, the end node will be node one
        {
            start_node_result[counter]=start_node+1;
            end_node_result[counter]=1;
            counter++;
        }
        mark=0;
    }
    t = clock() - t;
    cout<<"tiem for heap is : "<<t<<endl;

    print(start_node_result,end_node_result,mini_result,num_of_vertices,ios);

    ios<<"the total of the weight is : "<<total_value_path<<endl;
}
//---------------------heap list end-------------------------------------->>

//--------------------from here is the brute force----------------------------->>

void brute(float **weight_of_path,int num_of_vertices, ofstream& ios)
{
    
    ios<<"<-------------------result for the brute force-------------------------------->"<<endl;
    clock_t t; //to work out time
    t = clock();
    
    
    float** brute_path = new float* [num_of_vertices];//create a new array to store the data
    for (int i = 0; i < num_of_vertices; i++)//init the array
        brute_path[i] = new float[num_of_vertices];
    
    
    
    for(int i=0;i<num_of_vertices;i++)//copy the nodes to the new array
    {
        for(int j=0;j<num_of_vertices;j++)
        {
            brute_path[i][j]=weight_of_path[i][j];
        }
    }
    
    
    
    for(int j=1;j<num_of_vertices;j++)//modify the array, so choose each node from each row will be cover all possible situations
    {
        for(int i=0;i<num_of_vertices;i++)
        {
            if(i>=j)
            {
                brute_path[i][j]=brute_path[j-1][i+1];
            }
            
        }
    }
    
    float mini=0,total_mini=0;
    int start_node=0,end_node=0;
    for(int i=0;i<num_of_vertices-1;i++)//work out the result
    {
        //i try to build an array to make all the possible result in the array, so each time i pick one value from each row will work out the right result, but it only works some times, and most of the time the result seems not good
        
        mini=brute_path[i][1];
        for(int j=1;j<num_of_vertices;j++)
        {
            if(brute_path[i][j]<mini)
            {
                mini=brute_path[i][j];//change the array to put all possible numbers each time in to one row
                if(i<=j)
                {
                    end_node=i;
                    start_node=j;
                }
                else{
                    start_node=i;
                    end_node=j;
                }
            }
            
        }
        
        
        
        ios<<start_node+1<<" -> "<<end_node+1<<" "<<mini<<endl;
        total_mini+=mini;
        
    }

    
    ios<<"the total of the weight is : "<<total_mini<<endl;
    
    t = clock() - t;
    cout<<"time for brute is : "<<t<<endl;
    
    
}

//--------------------brute force end----------------------------

//--------------------from here is the prime array-----------------------------
void prim(float **weight_of_path,int num_of_vertices, ofstream& ios)//use prim to get the mst
{
    ios<<"<-------------------result for the prim-------------------------------->"<<endl;
    int nearst[num_of_vertices];//store the nearst node
    float mindist[num_of_vertices];//store the mindist
    int end_node=1;
    
    int start_node_result[num_of_vertices];//to store the result of node in the array to print
    int end_node_result[num_of_vertices];//to store the result of node in the array to print
    float mini_result[num_of_vertices];//to store the result of path to print
    int counter=0;//the counter of the node array
    int counter_mini=0;
    
    for(int i=1;i<num_of_vertices;i++)//start from node 1 all nearst set to 1 mindist equal to
    {
        nearst[i]=1;
        mindist[i]=weight_of_path[0][i];
    }
    
    clock_t t; //to work out time
    t = clock();
    
    
    int start_node=0;
    int mark=0;// a mark to check if the value have been change from the first time sort, to check connect to node one or not
    int first_time_mark=0;
    float total_value_path=0;
    for(int i=1;i<num_of_vertices;i++)//repeat n-1 times
    {
        float min= max_float;//set min to max
        for(int j=1;j<num_of_vertices;j++)//find the min value of mindist
        {
            if(mindist[j]>0&&mindist[j]<=min)
            {
                min=mindist[j];
                start_node=j;
                
                
            }
        }
        //cout<<" mini "<<min<<endl;
        mini_result[counter_mini]=min;
        counter_mini++;
        
        
        if(first_time_mark==0)//the first time out put 1 to the start node
        {
            //cout<<1<<" -> "<<start_node+1<<" "<<endl;
            start_node_result[counter]=1;
            end_node_result[counter]=start_node+1;
            counter++;
            first_time_mark=1;
        }
        
        total_value_path+=min;
        mindist[start_node]=-1;//the node already selected drop it
        
        for(int j=1;j<num_of_vertices;j++)// to find if there's new node connected to the last picked node less than the value in mindist
        {
            
            if(weight_of_path[j][start_node]<mindist[j])
            {
                mindist[j]=weight_of_path[j][start_node];// put new smallest value in the minist
                end_node=j+1;
                mark=1;//it is not the node connected to node one
                
            }
            
        }
        
        
        if(mark==1&&start_node+1!=end_node)//if node connect to the node one, the value have been changed form the first time sort, it will be a new node
        {
            start_node_result[counter]=start_node+1;
            end_node_result[counter]=end_node;
            counter++;
        }
        if(mark==0&&start_node+1!=end_node)//if connect to node one, the end node will be node one
        {
            start_node_result[counter]=start_node+1;
            end_node_result[counter]=1;
            counter++;
        }
        mark=0;
    }
    t = clock() - t;
    
    print(start_node_result,end_node_result,mini_result,num_of_vertices,ios);
    
    ios<<"the total of the weight is : "<<total_value_path<<endl;
    cout<<"time for prime is : "<<t<<endl;
}
//--------------------prim array end-------------------------

//-------------------from here is the read file founction----------
void readfile()
{
    node_list* head;//head of the link list
    //read the file
    char name[100];
    fstream ins;
    cout<<"pls input the file name: "<<endl;
    cin>>name;
    
    ins.open(name);
    if(!ins.good())//if cant open break
    {
        cout<<"wrong file name"<<endl;
    }
    
    
    ofstream ios;
    ios.open("output.txt");
    
    
    int num_of_vertices;
    ins>>num_of_vertices;//read the number of vertices in the array
    //float weight_of_path[num_of_vertices][num_of_vertices];
    
    
    float** weight_of_path = new float* [num_of_vertices];//the array store all the weight of the nodes
    for (int i = 0; i < num_of_vertices; i++)//init the array
        weight_of_path[i] = new float[num_of_vertices];
    
    for(int i=0;i<num_of_vertices;i++)//read in all the weight between the nodes store in the array
    {
        for(int j=0;j<num_of_vertices;j++)
        {
            ins>>weight_of_path[i][j];
            creat_node_list_add_node(weight_of_path[i][j],head);//add node to the link list
            
        }
    }
    
    brute(weight_of_path,num_of_vertices,ios);
    prim(weight_of_path,num_of_vertices,ios);
    heap(head,weight_of_path,num_of_vertices,ios);


}
//-----------read file end--------------

int main(int argc, const char * argv[]) {
    readfile();
    return 0;
}

