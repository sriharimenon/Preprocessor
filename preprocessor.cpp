#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#define reson 400000
#define resoe 500000

using namespace std;

long double scale, nx[reson], ny[reson], dist, minidist=1000.00;
   int nodes, neles, n, n1[resoe], n2[resoe], n3[resoe], neighbornode[reson][13]={0}, counter=0, neighborno[reson], dummy, k=1, boundnodes[20000][5],ntype[20000], bnodes, bntype, m=2, closeneig[20000][3], be[20000][3]={0};

int main()
{
   
   cout<<"\t\t\t\tTHE PREPROCESSOR\n\nInstructions for use:\n1. Rename the mesh file to mesh.dat\n2. Make sure that there are no words in the file(e for power of 10 is tolerated) \n3. go through the README file to copy the format of the input mesh file compatible with the app and to understand the app's limits \n\nAfter the above is made sure of, press enter to continue";
   cin.ignore();

	ifstream infile("mesh.dat");
   ofstream gridfile("grid.dat");
   ofstream bcfile("bc.in");
   ofstream befile("be.in");
   ofstream visfile("visual.dat");

   infile>>nodes>>neles;

   visfile<<nodes<<'\t'<<neles<<'\t'<<'3'<<endl;

   cout<<"\nenter scale of conversion(for example, to convert coordinates in mm to meters, enter 0.001. enter 1 if no unit conversion is desired)";
   cin>>scale;

    //loop to read nodes and co-ordinates
   for(int i=1;i<=nodes;i++)
   	{
    	infile>>n;
    	infile>>nx[n]>>ny[n];

      ny[n]*=scale;
      nx[n]*=scale;

      visfile<<n<<'\t'<<nx[n]<<'\t'<<ny[n]<<'\t'<<"0.00"<<endl;
   	}

      for(int i=1;i<=nodes;i++)neighbornode[i][1]=i;

    //loop to read elements
      for (int j=1;j<=neles;j++)
   	{
      infile>>n>>dummy>>dummy>>n1[j]>>n2[j]>>n3[j];
      visfile<<n<<'\t'<<n1[j]<<'\t'<<n2[j]<<'\t'<<n3[j]<<'\t'<<'0'<<endl;

      for(int i=1;i<=nodes;i++)	{

      											if(i==n1[j]){	while(neighbornode[i][k]!=0){if(neighbornode[i][k]==n2[j])counter++;k++;};
                                       					if(counter==0)neighbornode[i][k]=n2[j]; k=1; counter=0;
                                                      while(neighbornode[i][k]!=0){if(neighbornode[i][k]==n3[j])counter++;k++;};
                                                      if(counter==0)neighbornode[i][k]=n3[j]; k=1; counter=0;
                                                      }

                                       if(i==n2[j]){	while(neighbornode[i][k]!=0){if(neighbornode[i][k]==n1[j])counter++;k++;};
                                       					if(counter==0)neighbornode[i][k]=n1[j];k=1; counter=0;
                                                      while(neighbornode[i][k]!=0){if(neighbornode[i][k]==n3[j])counter++;k++;};
                                                      if(counter==0)neighbornode[i][k]=n3[j];k=1; counter=0;
                                                      }

                                       if(i==n3[j]){	while(neighbornode[i][k]!=0){if(neighbornode[i][k]==n2[j])counter++;k++;};
                                       					if(counter==0)neighbornode[i][k]=n2[j];k=1; counter=0;
                                                      while(neighbornode[i][k]!=0){if(neighbornode[i][k]==n1[j])counter++;k++;};
                                                      if(counter==0)neighbornode[i][k]=n1[j]; counter=0;k=1;
                                                      }

      										while(neighbornode[i][++neighborno[i]]!=0);
                                    neighborno[i]-=2;
      									}
      }

      cout<<endl<<"visual.dat written!"<<endl;


      //writing grid.dat
      gridfile<<nodes<<'\t'<<neles<<endl;
      for(int i=1;i<=nodes;i++){	gridfile<<i<<'\t'<<setprecision(4)<<nx[i]<<"\t\t"<<setprecision(4)<<ny[i]<<"\t\t"<<neighborno[i]<<'\t';
      									for(int j=2; j<=neighborno[i]+1; j++)gridfile<<neighbornode[i][j]<<'\t';
                                 gridfile<<endl;
                                 }
      for(int i=1;i<=neles+1;i++)gridfile<<endl<<i<<'\t'<<n1[i]<<'\t'<<n2[i]<<'\t'<<n3[i];

     cout<<endl<<"grid.dat written!"<<endl;

     int totbnodes=1;

     infile>>bnodes>>bntype;
     while(bnodes!=0&&bntype!=0){for(int i=totbnodes; i<=totbnodes+bnodes-1; i++){infile>>boundnodes[i][1];ntype[i]=bntype;}
     										totbnodes+=bnodes; bnodes=0; bntype=0; infile>>bnodes>>bntype;
                                 }

		totbnodes--;

      counter=0;
      for(int i=1;i<=totbnodes;i++)
      {for(int j=1;j<nodes;j++)if(boundnodes[i][1]==neighbornode[j][1])
      																						for(int k=1; k<=neighborno[j]; k++)
                                                                        												{for(int l=1;l<=totbnodes;l++)if(neighbornode[j][k]!=boundnodes[l][1])counter++;if(counter==totbnodes)boundnodes[i][m++]=neighbornode[j][k];counter=0;}m=2;}

		for(int i=1;i<=totbnodes;i++){for(int q=2;q<5;q++)if(boundnodes[i][q]!=0){	dist=sqrt((nx[boundnodes[i][1]]-nx[boundnodes[i][q]])*(nx[boundnodes[i][1]]-nx[boundnodes[i][q]])+(ny[boundnodes[i][1]]-ny[boundnodes[i][q]])*(ny[boundnodes[i][1]]-ny[boundnodes[i][q]]));
      																										closeneig[i][1]=boundnodes[i][1];
                                                                                    if (dist<=minidist){minidist=dist; closeneig[i][2]=boundnodes[i][q];}
                                                                                  }
      											minidist=1000.00;
                                    }
      //writing bc.in
      bcfile<<totbnodes<<endl;
      for(int i=1; i<=totbnodes; i++)bcfile<<closeneig[i][1]<<'\t'<<ntype[i]<<'\t'<<closeneig[i][2]<<endl;

      cout<<endl<<"bc.in written!"<<endl;

      int z=1; counter=0;

      for(int i=1; i<=neles; i++)for(int j=1; j<=totbnodes; j++){if(n1[i]==closeneig[j][1]){	for(int k=1; k<=totbnodes; k++)if(n2[i]==closeneig[k][1]){while(be[z][1]!=0){if(be[z][1]==i&&be[z][2]==1)counter++;z++;} if (counter==0){be[z][1]=i;be[z][2]=1;} z=1;counter=0;}
                                                                                             for(int k=1; k<=totbnodes; k++)if(n3[i]==closeneig[k][1]){while(be[z][1]!=0){if(be[z][1]==i&&be[z][2]==3)counter++;z++;} if (counter==0){be[z][1]=i;be[z][2]=3;} z=1;counter=0;}
                                                                                            }

                                                                 else if(n2[i]==closeneig[j][1])for(int k=1; k<=totbnodes; k++)if(n3[i]==closeneig[k][1]){while(be[z][1]!=0){if(be[z][1]==i&&be[z][2]==2)counter++;z++;} if (counter==0){be[z][1]=i;be[z][2]=2;} z=1;counter=0;}
                                                                 }
      //writing be.in
      z=1;
      while(be[z][1]!=0)z++;
      befile<<z<<endl;

      z=1;
      while(be[z][1]!=0){befile<<be[z][1]<<'\t'<<be[z][2]<<endl;z++;}

      cout<<endl<<"be.in written!"<<endl;

		getch();
}
