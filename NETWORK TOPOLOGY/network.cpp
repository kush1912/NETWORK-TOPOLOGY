/****************************************
* Title: NETWORK TOPOLOGY               *
* IDE: CODEBLOCKS C++                   *
* Dated: APRIL 04,2018                  *
****************************************/



#include <graphics.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <bits/stdc++.h>
#include<vector>

# define inf 99999


using namespace std;

int n;

vector<int>v;
int c[15][15];


struct point
{
    double x;
    double y;
};

void initgraphic()
{
int gd=DETECT, gm;
initgraph(&gd, &gm,"C:\\Users\Kushwaha\\Desktop\\network ");
}

void create(int a[][15],int n)
{
    initgraphic();
    initwindow(1366, 768, "NETWORK TOPOLOGY");

    double   midx = 650, midy = 350;
    setlinestyle(SOLID_LINE,0,THICK_WIDTH);

    rectangle(0,0,midx,midy);
    setfillstyle(SOLID_FILL, 3);
    floodfill(1, 1, RED);

    struct point c[n];
    double rd = 3.14/180;
    double r = 200;
    char cn[2];


    for (int i = 0; i < n; i++)
    {
        c[i].x = midx + r * cos(rd * (360.0/n) * i);
        c[i].y = midy + r * sin(rd * (360.0/n) * i);
        circle(c[i].x, c[i].y, 20);
        if (i >= 3)
        {
            setbkcolor(i+1);
            setfillstyle(SOLID_FILL, i+1);
        }
        else
        {
            setbkcolor(i);
            setfillstyle(SOLID_FILL, i);
        }
        floodfill(c[i].x, c[i].y, WHITE);

        outtextxy(c[i].x-8,c[i].y-8,"C");
        itoa(i,cn,10);
        outtextxy(c[i].x,c[i].y-8,cn);
        delay(500);
    }

    char w[3];
    setbkcolor(CYAN);
    for(int i=0;i<n;i++)
    {
        for(int j=i;j<n;j++)
        {
           if((a[i][j]<inf)&&(i!=j))
           {
               // cout << a[i][j] << ' ' << i << ' ' << j << endl;
            if(a[i][j] > 0)
            {
                //cout << i << " " << j << endl;
                setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
                line(c[i].x,c[i].y,c[j].x,c[j].y);
                itoa(a[i][j],w,10);
                outtextxy((c[i].x+c[j].x)/2-30,(c[i].y+c[j].y)/2,w);
                delay(250);
            }
            else if (a[i][j] < 0)
            {
                setlinestyle(DOTTED_LINE, 0, NORM_WIDTH);
                line(c[i].x,c[i].y,c[j].x,c[j].y);
                //toa(-a[i][j],w,10);
                //outtextxy((c[i].x+c[j].x)/2-30,(c[i].y+c[j].y)/2,w);
                delay(250);
            }
            }
        }
    }
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);

    for (int i = 0; i < n; i++)
    {
        c[i].x = midx + r * cos(rd * (360.0/n) * i);
        c[i].y = midy + r * sin(rd * (360.0/n) * i);
        setcolor(0);
        circle(c[i].x, c[i].y, 20);
        if (i >= 3)
        {
            setbkcolor(i+1);
            setfillstyle(SOLID_FILL, i+1);
        }
        else
        {
            setbkcolor(i);
            setfillstyle(SOLID_FILL, i);
        }
        floodfill(c[i].x, c[i].y, 0);
        setcolor(WHITE);
        circle(c[i].x, c[i].y, 20);

        outtextxy(c[i].x-8,c[i].y-8,"C");
        itoa(i,cn,10);
        outtextxy(c[i].x,c[i].y-8,cn);
    }
    delay(5);
}




int minKey(int key[], bool mstSet[],int n)
{
   int min = INT_MAX, min_index;

   for (int v = 0; v < n; v++)
     if (mstSet[v] == false && key[v] < min)
         min = key[v], min_index = v;

   return min_index;
}

int printMST(int parent[], int n, int a[][15])
{
      int cost=0;
      printf("Edge   Weight\n");
      for (int i = 1; i < n; i++)
      {
          cost+=a[i][parent[i]];
          printf("%d - %d    %d \n", parent[i], i, a[i][parent[i]]);
      }
      cout<<"TOTAL COST FOR SETTING THE NETWORK IN TREE TOPOLOGY IS: "<<cost<<endl<<endl;
      int b[n][15];
      for(int i=0;i<n;i++)
     {
         for(int j=0;j<n;j++)
         {
             b[i][j]=0;
         }
     }

      /*for(int i=0;i<n;i++)
      {
          b[parent[i]][i]=a[i][parent[i]];
      }
*/
      for (int i = 0; i < n; i++)
      {
          for (int j = 0; j < n; j++)
          {
              if (parent[i] == j)
              {
                  b[j][i] = b[i][j] = a[i][j];
              }
              else
              {
                  if(a[i][j]!=inf)
                   b[i][j] = b[j][i] = -a[i][j];
              }
              //cout << b[i][j] << "\t";
          }
          //cout << endl;
      }

    create(b, n);
    return cost;
}

int tree_topology(int graph[][15],int n)
{
     int parent[n];
     int key[n];
     bool mstSet[n];

        for (int i = 0; i < n; i++)
        key[i] = INT_MAX, mstSet[i] = false;

     key[0] = 0;
     parent[0] = -1;

     for (int c = 0; c < n-1; c++)
     {
        int u = minKey(key, mstSet,n);
        mstSet[u] = true;
     for (int v = 1; v < n; v++)
     {
          if (graph[u][v] && mstSet[v] == false && graph[u][v] <  key[v])
              parent[v]  = u, key[v] = graph[u][v];
     }
     }
    int m = printMST(parent, n, graph);
    return m;
}

void printSolution(int dist[][15], int n);

int floydWarshall (int graph[][15], int index,int n)
{
    int cost=0;
    for (int i = 0; i < n; i ++)
    {
        for (int j = 0; j < n; j ++)
        {
            if (i != j && !graph[i][j])
            {
                graph[i][j] = inf;
            }
        }
    }
    int dist[15][15], i, j, k;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            dist[i][j] = graph[i][j];

    for (k = 0; k < n; k++)
    {
        // Pick all vertices as source one by one
        for (i = 0; i < n; i++)
        {

            for (j = 0; j < n; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    for(int y=0; y<n; y++)
    {
        for(int x=0; x<n; x++)
        {
          if(y==index)
          {
              c[y][x]=c[x][y]=dist[index][x];
          }
          else
          {
              c[y][x]=inf;
          }
        }
    }

    for(int i=0;i<n;i++)
    {
        cost+=c[index][i];
    }

    cout<<"TOTAL COST FOR SETTING THE NETWORK IN STAR TOPOLOGY IS: "<<cost<<endl<<endl;
    create(c,n);
    for (int i = 0; i < n; i ++)
    {
        for (int j = 0; j < n; j ++)
        {
            if (i != j && graph[i][j] == inf)
            {
                graph[i][j] = 0;
            }
        }
    }
    return cost;
}

int deg(int a[][15],int n,int degree[])
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
             if(a[i][j]<inf&&a[i][j]!=0)
             {
                 degree[i]++;
             }
        }
    }

    int s,d=0;
    for(int i=0;i<n;i++)
        {
           if(d<degree[i])
           {
               d=degree[i];
               s=i;
           }
//           cout<<degree[i]<<" ";
        }
        return s;
}

int arr[15];
void printSolution(int path[]);

bool isSafe(int v, int graph[][15], int path[], int pos)
{

    if (graph [ path[pos-1] ][ v ] == 0)
        return false;


    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}
int mini=9999;
/* A recursive utility function to solve hamiltonian cycle problem */

bool hamCycleUtil(int graph[][15], int path[], int pos)
{
    /* base case: If all vertices are included in Hamiltonian Cycle */
    if (pos == n)
    {

        if ( graph[ path[pos-1] ][ path[0] ])
           { int sum=0;
               for(int i=1;i<n;i++)
               {
                   //printf("%d",path[i]);
                   sum=graph[path[i-1]][path[i]];
               }
              if (sum<mini)
                for(int i=1;i<n;i++)
               arr[i]=path[i];

               return true;
           }
        else
          return false;
    }


    for (int v = 1; v < n; v++)
    {
        /* Check if this vertex can be added to Hamiltonian Cycle */
        if (isSafe(v, graph, path, pos))
        {
            path[pos] = v;

            /* recur to construct rest of the path */
            if (hamCycleUtil (graph, path, pos+1) == true)
                continue;

            /* If adding vertex v doesn't lead to a solution,
               then remove it */
            path[pos] = -1;
        }
    }


    return false;
}


bool hamCycle(int graph[][15])
{
    int *path = new int[n];
    for (int i = 0; i < n; i++)
        path[i] = -1;

    path[0] = 0;

    if ( hamCycleUtil(graph, path, 1) == false )
    {
        //printf("\nSolution does not exist");
        return false;
    }
     //hamCycleUtil(graph, path, 1);


    return true;
}

/* A utility function to print solution */
void printRing(int path[])
{
    printf ("Solution Exists:"
            " Following is one Hamiltonian Cycle \n");
    for (int i = 0; i < n; i++)
        printf(" %d ", path[i]);

    // Let us print the first vertex again to show the complete cycle
    printf(" %d ", path[0]);
    printf("\n");
}

void ring(int graph[][15], int n)
{
   int cost=0;
    hamCycle(graph);
    printRing(arr);
    int b[n][15];
    for (int i = 0; i < n; i ++)
    {
        for (int j = 0; j < n; j ++)
        {
            b[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++)
    {
        //cout << arr[i] << "->" << arr[i+1] << endl;
        b[arr[i+1]][arr[i]] = graph[arr[i+1]][arr[i]];
        b[arr[i]][arr[i+1]] = graph[arr[i]][arr[i+1]];
        cost+=graph[arr[i]][arr[i+1]];
    }

    cout<<"TOTAL COST FOR SETTING THE NETWORK IN RING TOPOLOGY IS: "<<cost<<endl<<endl;
    /*
    for (int i = 0; i < n; i ++)
    {
        for (int j = 0; j < n; j ++)
        {
            cout << b[i][j] << " ";
        }
        cout << endl;
    }
    */
    create(b, n);
}



int main()
{
   int c,t1,t2;
   cout<<"ENTER THE NO. OF COMPUTERS: ";
   cin>>n;
   int a[n][15];

   for(int i=0;i<n;i++)
   {
       for(int j=0;j<n;j++)
        {
            a[i][j]=0;
        }
   }

/*
    do{
        cout<<"Enter the NODES and COST between the Nodes : ";
        cin>>t1>>t2>>c;
        a[t1][t2]=a[t2][t1]=c;
     }while(t1>=0);
*/

    ifstream input_file;
    input_file.open("in.txt");
    while (!input_file.eof())
    {
        input_file >> t1 >> t2 >> c;
        a[t1][t2] = a[t2][t1] = c;
    }

   create(a,n);
   tree_topology(a,n);



int degree[n]={0};
int s=deg(a,n,degree);
floydWarshall(a,s,n);
/*
for (int i = 0; i < n; i++)
{
    for (int j = 0; j < n; j++)
    {
        cout << a[i][j] << " ";
    }
    cout << endl;
}

*/

ring(a,n);

/*
if(c1>c2)&&(c1>c3)
{
    cout<<"TREE TOPOLOGY IS THE BEST TOPOLOGY!;
}

if(c2>c1)&&(c2>c3)
{
    cout<<"STAR TOPOLOGY IS THE BEST TOPOLOGY!;
}

if(c3>c1)&&(c3>c2)
{
    cout<<"RING TOPOLOGY IS THE BEST TOPOLOGY!;
}
*/


cout<<endl<<endl<<"SUBMITTED TO:-"<<endl;
cout<<"Mrs. INDU CHAWLA"<<endl;
cout<<endl<<endl<<"SUBMITTED BY:-"<<endl;
cout<<"AJAY KUSHWAHA"<<"             "<<"16104013"<<endl;

   while(1)
   {

   }
   return 0;
}
