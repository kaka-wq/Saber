#include<iostream>
#include <stdio.h>
#include <math.h>


#include <stdint.h>
#include <Windows.h>
using namespace std;



int main()
{
	//参数1
	int n=256;
	int eq=13;
	int q=8192;//q=2^eq
	int ep=10;
	int p=1024;//p=2^ep



	int et=3;
	int t=8;//2^et
	int Mpt=128;//Mpt=2^(ep-et)=2^7
	int h2=196;//h2=256-2^(ep-et-1)+4
	int eta=5;
	int pv=11;//2*eta+1 possible values of S_t
	int mpv=2048;//2^pv
	int array1[11]={0};//record m_j correspongding to S_t,j!=0
	int array2[11]={0};//recover m_0 correspongding to S_t
	int *array3;
    array3=(int*)calloc(2048,sizeof(int));
	//int array3[2048]={0};//find out the differnt bit strings and record the number of each bit string in array3
	int *array4;
    array4=(int*)calloc(2048,sizeof(int));
	//int array4[2048]={0};//record the differnt bit strings in array4
	int count=0;//the number of the differnt bit strings
	int array5[11][15]={0};//the row is the possible values of S_t and the column is the number of the differnt bit strings
	int array6[11][6]={0};//choose 5 columns  from this array5, so that each row of the selected matrix is different
	int column=6;////choose 5 columns  from this array5



	int a,b;//a,b
	int st;//S_t
	int temp;
	int c,d,e,f,g,h,l,m,o,r,s,u,v;
	bool flag;
	int sum;
	int mula;
	int i,j,k,tt;
	
	int controloutput=0;//
	int number=0;//the number of all the results satisfies the conditions
	int number_better=0;//the number of all the better results 
	int i_output1,j_output1,k_output1,l_output1,m_output1,o_output1;//output the first result
	int i_output2,j_output2,k_output2,l_output2;//output one of the better result
	int count_i=0,count_j=0,count_k=0,count_l=0,count_m=0,count_o=0;// count the number of (a,b) pair satisfing the conditions in the first result or the better result
	bool flag_i=true,flag_j=true,flag_k=true,flag_l=true,flag_m=true,flag_o=true;

	//a in {0,...,(2^et)-1},b in {0,...,(2^ep)-1}
	for (b = 0; b<p; b++)
	{
		for (a = 0; a<t; a++)
		{
			flag=true;
			for(st=0;st<pv;st++)//**************
			{
				array1[st]=(b*(st-eta)+h2)%p;//*********************
				if(array1[st]<0)
				{
					array1[st]=array1[st]+p;
				}
				array1[st]=array1[st]>>(ep-1);
				if(array1[st]!=0)
				{
					flag=false;
				}
			}

			if(flag)
			{
				for(st=0;st<pv;st++)//**************************
				{
					array2[st]=(b*(st-eta)-a*Mpt+h2)%p;//******************
					if(array1[st]<0)
					{
						array2[st]=array2[st]+p;
					}
					array2[st]=array2[st]>>(ep-1);
				}
			}
			
		   //for a (a, b) pair, m_0's values, when S_t takes 5 different values, constitutes a 5-bit string 
		   //since the length of the bit string is 5, it has 2^5 possibles and a large number of (a, b) pairs corresponds to the same bit string 
           //convert the bit strings into integers for the convenience of finding the same bit string 
			sum=0;
			mula=1;
			for(st=0;st<pv;st++)//5 possible values
			{
				sum=sum+array2[st]*mula;

				mula=mula*2;
			}
			array3[sum]++;//find out the differnt bit strings and count the number of each bit string 

		}
	}


	//count the number of different bit strings and recored the differnt bit strings in array4
	j=0;
	for(i=0;i<mpv;i++)//since the length of the bit string is 5, it has 2^5 possibles
	{
		if (array3[i]!=0)
		{
			array4[j]=i;
			count++;
			j++;
			cout<<"array3["<<i<<"]="<<array3[i]<<endl;
		}

	}
	cout<<"there are "<<count<<" different bit strings and they are: "<<endl;//count=10

	for (j=0;j<count;j++)//count=10
	{
		cout<<"array4["<<j<<"]"<<array4[j]<<endl;
	}

	//after finding out the differnt bit strings and output them 
	for (j=0;j<count;j++)//count=10
	{
		temp=array4[j];
		array5[0][j]=temp%2;
		for(i=1;i<pv;i++)//5 possible values
		{
			temp=temp/2;
			array5[i][j]=temp%2;
		}
	}
	// the each column of array5 is the bit string
	for (j=0;j<count;j++)//count=10
	{
		//cout<<"array5["<<j<<"]="<<array4[j]<<"="<<endl;

		for(i=0;i<pv;i++)//5 possible values
		{
			cout<<array5[i][j];
		}
		cout<<endl;
	}
	cout<<"since the bit strings corresponding to -1 and 0 are all the same, S_t=-1 or 0 can't be distinguished."<<endl;
	cout<<endl;

   //Remove a large number of duplicates and we get a 5-by-count matrix.
	//This matrix is much smaller than the previous 5-by-(d_v*d_u) matrix
   //We choose as few columns as possible from this matrix, so that each row of the selected matrix is different 
	//Since S_t has 5 possible values, at least 3 columns are needed ,but there are no 3 columns that meet the conditions
	//In particualr, we choose 4 columns
	for (i=0;i<count;i++)//count=10
		for(j=i+1;j<count;j++)//count=10
			for(k=j+1;k<count;k++)//count=10	
				for(l=k+1;l<count;l++)//count=10	
					for(m=l+1;m<count;m++)//count=10	
						for(o=m+1;o<count;o++)//count=10
							//for(r=o+1;r<count;r++)//count=10
								//for(s=r+1;s<count;s++)//count=10
									//for(u=s+1;u<count;u++)//count=10
				{
					flag=true;
					for(tt=0;tt<5;tt++)//5 possible values
					{
						array6[tt][0]=array5[tt][i];
						array6[tt][1]=array5[tt][j];
						array6[tt][2]=array5[tt][k];
						array6[tt][3]=array5[tt][l];
						array6[tt][4]=array5[tt][m];
						array6[tt][5]=array5[tt][o];
						//array6[tt][6]=array5[tt][r];
						//array6[tt][7]=array5[tt][s];
						//array6[tt][8]=array5[tt][u];
					}
					for(tt=5;tt<10;tt++)
					{
						array6[tt][0]=array5[tt+1][i];
						array6[tt][1]=array5[tt+1][j];
						array6[tt][2]=array5[tt+1][k];
						array6[tt][3]=array5[tt+1][l];
						array6[tt][4]=array5[tt+1][m];
						array6[tt][5]=array5[tt+1][o];
						//array6[tt][6]=array5[tt+1][r];
						//array6[tt][7]=array5[tt+1][s];
						//array6[tt][8]=array5[tt+1][u];
					}

					f=pv-2;//5 possible values
					for(d=0;d<pv-1;d++)//5 possible values
					{	
						for(e=1;e<=f;e++)
						{
							if(array6[d][0]==array6[d+e][0] && array6[d][1]==array6[d+e][1] && array6[d][2]==array6[d+e][2] && array6[d][3]==array6[d+e][3] && array6[d][4]==array6[d+e][4] && array6[d][5]==array6[d+e][5]  /*&& array6[d][6]==array6[d+e][6]  && array6[d][7]==array6[d+e][7] &&  array6[d][8]==array6[d+e][8]*/)
							{
								flag=false;
								break;
							}

						}
						f=f-1;
					}

					if(flag)
					{
						number++;//record all the results that meet the conditions
						if(controloutput==0)//only output the first result
						{
							cout<<"the first result is: "<<endl;
							controloutput++;
							for(g=0;g<pv;g++)//5 possible values
							{
								for(h=0;h<column;h++)//try to distinguish each coefficient of s using 4 queries
								{
									cout<<array6[g][h];
								}
								cout<<endl;
							}

							cout<<"they are taken from columns"<<" "<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<m<<" "<<o<<" of the  array5"<<endl;
							//cout<<"i="<<i<<", j="<<j<<", k="<<k<<", l="<<l<<endl;
							cout<<" "<<endl;

							//record the 4 columns in order to find the corresponding (a,b) pair next 
							i_output1=i;
							j_output1=j;
							k_output1=k;
							l_output1=l;
							o_output1=o;
							m_output1=m;
						}
                        /*
						if (array6[2][0]!=array6[0][0] && array6[2][0]!=array6[1][0]  && array6[2][0]!=array6[3][0] && array6[2][0]!=array6[4][0])
						{
							if(controloutput==1)
							{
								controloutput++;
								for(g=0;g<5;g++)//5 possible values
								{
									for(h=0;h<4;h++)//try to distinguish each coefficient of s using 3 queries
									{
										cout<<array6[g][h];
									}
									cout<<endl;
								}

								cout<<"i="<<i<<"j="<<j<<"k="<<k<<"l="<<l<<endl;
								cout<<" "<<endl;
							}
						}
						*/
/*
						//Output a better result
						if ((array6[2][0]+2*array6[2][1])!=(array6[0][0]+2*array6[0][1]) && (array6[2][0]+2*array6[2][1])!=(array6[1][0]+2*array6[1][1])  && (array6[2][0]+2*array6[2][1])!=(array6[3][0]+2*array6[3][1]) && (array6[2][0]+2*array6[2][1])!=(array6[4][0]+2*array6[4][1]))
						{
							number_better++;
							if(controloutput==1)
							{
								cout<<"a better result is: "<<endl;
								controloutput++;
								for(g=0;g<pv;g++)//5 possible values
								{
									for(h=0;h<column;h++)//try to distinguish each coefficient of s using 3 queries
									{
										cout<<array6[g][h];
									}
									cout<<endl;
								}

								cout<<"they are taken from columns"<<" "<<i<<" "<<j<<" "<<k<<" "<<l<<" of the  array5"<<endl;
								//cout<<"i="<<i<<"j="<<j<<"k="<<k<<"l="<<l<<endl;
								cout<<" "<<endl;
								i_output2=i;
								j_output2=j;
								k_output2=k;
								l_output2=l;
							}
						}
*/
					}	
				}

				//search the corresponding (a,b) of the first result;
				cout<<"there are "<<number<<" results,";
				cout<<"in order to output the first result,"<<endl;
				for (b = 0; b<p; b++)
				{
					for (a = 0; a<t; a++)
					{
						flag=true;
						for(st=0;st<pv;st++)//**************
						{
							array1[st]=(b*(st-eta)+h2)%p;//*********************
							if(array1[st]<0)
							{
								array1[st]=array1[st]+p;
							}
							array1[st]=array1[st]>>(ep-1);
							if(array1[st]!=0)
							{
								flag=false;
							}
						}

						if(flag)
						{
							for(st=0;st<pv;st++)//**************************
							{
								array2[st]=(b*(st-eta)-a*Mpt+h2)%p;//******************
								if(array1[st]<0)
								{
									array2[st]=array2[st]+p;
								}
								array2[st]=array2[st]>>(ep-1);
							}
						}

						//for a (a, b) pair, m_0's values, when S_t takes 5 different values, constitutes a 5-bit string 
						//since the length of the bit string is 5, it has 2^5 possibles and a large number of (a, b) pairs corresponds to the same bit string 
						//convert the bit strings into integers for the convenience of finding the same bit string 
						sum=0;
						mula=1;
						for(st=0;st<pv;st++)//5 possible values
						{
							sum=sum+array2[st]*mula;

							mula=mula*2;
						}
						if(sum==array4[i_output1])
						{
							count_i++;
							if (flag_i)
							{
								flag_i=false;cout<<"the 1st query is "<<"a="<<a<<", b="<<b<<endl;
							}
						}
						if(sum==(array4[j_output1]))
						{
							count_j++;
							if (flag_j)
							{
								flag_j=false;
								cout<<"the 2nd query is "<<"a="<<a<<", b="<<b<<endl;
							}
						}
						if(sum==array4[k_output1]){count_k++;if (flag_k){flag_k=false;cout<<"the 3rd query is "<<"a="<<a<<", b="<<b<<endl;}}
						if(sum==array4[l_output1]){count_l++;if (flag_l){flag_l=false;cout<<"the 4th query is "<<"a="<<a<<", b="<<b<<endl;}}
						if(sum==array4[m_output1]){count_m++;if (flag_m){flag_m=false;cout<<"the 5td query is "<<"a="<<a<<", b="<<b<<endl;}}
						if(sum==array4[o_output1]){count_o++;if (flag_o){flag_o=false;cout<<"the 6th query is "<<"a="<<a<<", b="<<b<<endl;}}
					}
				}

				cout<<"the 1st query has "<<count_i<<" (a,b) pairs and we take the first one"<<endl;
				cout<<"the 2nd query has "<<count_j<<" (a,b) pairs and we take the first one"<<endl;
				cout<<"the 3rd query has "<<count_k<<" (a,b) pairs and we take the first one"<<endl;
				cout<<"the 4th query has "<<count_l<<" (a,b) pairs and we take the first one"<<endl;
				cout<<"the 5rd query has "<<count_m<<" (a,b) pairs and we take the first one"<<endl;
				cout<<"the 6th query has "<<count_o<<" (a,b) pairs and we take the first one"<<endl;
				cout<<endl;

/*
				//search the corresponding (a,b) of a better result;
				cout<<"there are "<<number_better<<" better results,";
				cout<<"in order to output the better result above,"<<endl;
				flag_i=true; 
				flag_j=true;
				flag_k=true;
				flag_l=true;
				count_i=0;
				count_j=0;
				count_k=0;
				count_l=0;
				for (b = 0; b<p; b++)
				{
					for (a = 0; a<t; a++)
					{
						flag=true;
						for(st=0;st<pv;st++)//**************
						{
							array1[st]=(b*(st-eta)+h2)%p;//*********************
							if(array1[st]<0)
							{
								array1[st]=array1[st]+p;
							}
							array1[st]=array1[st]>>(ep-1);
							if(array1[st]!=0)
							{
								flag=false;
							}
						}

						if(flag)
						{
							for(st=0;st<pv;st++)//**************************
							{
								array2[st]=(b*(st-eta)-a*Mpt+h2)%p;//******************
								if(array1[st]<0)
								{
									array2[st]=array2[st]+p;
								}
								array2[st]=array2[st]>>(ep-1);
							}
						}

						//for a (a, b) pair, m_0's values, when S_t takes 5 different values, constitutes a 5-bit string 
						//since the length of the bit string is 5, it has 2^5 possibles and a large number of (a, b) pairs corresponds to the same bit string 
						//convert the bit strings into integers for the convenience of finding the same bit string 
						sum=0;
						mula=1;
						for(st=0;st<pv;st++)//5 possible values
						{
							sum=sum+array2[st]*mula;

							mula=mula*2;
						}
						if(sum==array4[i_output2])
						{
							count_i++;
							if (flag_i)
							{
								flag_i=false;cout<<"the 1st query is "<<"a="<<a<<", b="<<b<<endl;
							}
						}
						if(sum==(array4[j_output2]))
						{
							count_j++;
							if (flag_j)
							{
								flag_j=false;
								cout<<"the 2nd query is "<<"a="<<a<<", b="<<b<<endl;
							}
						}
						if(sum==array4[k_output2]){count_k++;if (flag_k){flag_k=false;cout<<"the 3rd query is "<<"a="<<a<<", b="<<b<<endl;}}
						if(sum==array4[l_output2]){count_l++;if (flag_l){flag_l=false;cout<<"the 4th query is "<<"a="<<a<<", b="<<b<<endl;}}
					}
				}
				cout<<"the 1st query has "<<count_i<<" (a,b) pairs and we take the first one"<<endl;
				cout<<"the 2nd query has "<<count_j<<" (a,b) pairs and we take the first one"<<endl;
				cout<<"the 3rd query has "<<count_k<<" (a,b) pairs and we take the first one"<<endl;
				cout<<"the 4th query has "<<count_l<<" (a,b) pairs and we take the first one"<<endl;
				cout<<endl;
*/				
					//cout<<"number="<<number<<"count_i="<<count_i<<"count_j="<<count_j<<"count_k="<<count_k<<"count_l="<<count_l<<endl;
					cin>>c;
				return 0;
}

/*
int main()
{
	int a;
	int b;
	int c,d,e,f,g,h;
	double Dp = 2.0/1024;//ep=10
	int p=1024;

	//参数2*****************
	int t=8;//et=3
	int Mpt=128;//et=3,ep-et=7,pt=2^(ep-et)=2^7
	int h2=196;//256+4-mpt/2
	int array1[11]={0};
	int array2[11]={0};
	int array3[2048]={0};//2^11
	int count=0;
	int array4[26]={0};
	int array5[11][26]={0};
	int array6[11][6]={0};


	int i;
	int j;
    int k,s,u,v;
	bool flag=true;
	int sum;
	int mula;
	int temp;
	

	for (b = 0; b<p; b++)
	{
		for (a = 0; a<t; a++)
		{
			flag=true;
			for(i=0;i<11;i++)//**************
			{
				array1[i]=int((b*(i-5)+h2)*Dp+0.5)%2;//*********************
				if(array1[i]!=0)
				{
					flag=false;
				}
			}

			if(flag)
			{
				for(i=0;i<11;i++)//**************************
				{
					array2[i]=int((b*(i-5)-a*Mpt+h2)*Dp+0.5)%2;//******************
					if(array2[i]<0)
					{
						array2[i]=-array2[i];
					}
				}
			}

			sum=0;
			mula=1;
			for(i=0;i<11;i++)//******************
			{
				sum=sum+array2[i]*mula;
				
				mula=mula*2;
			}
			array3[sum]++;
			if(sum==1566)
			{cout<<"a="<<a<<"b="<<b<<endl;
			}
		}
	}

	cin>>c;
	return 0;
}
*/


/*
#include<iostream>
#include <stdio.h>
#include <math.h>


#include <stdint.h>
#include <Windows.h>
using namespace std;


//3个数

int main()
{
	int a;
	int b;
	int c;
	int array1[32]={0};//顺序初始化
	int i;


	//参数1

	double v = 3329.0/8;//dv=3
	double u = 3329.0/1024;//du=10



	//参数2

	//double v = 3329.0/16;//dv=4
	//double u = 3329.0/1024;//du=10



	//参数3

	//double v = 3329.0/32;//dv=5
	//double u = 3329.0/2048;//du=11



	double A1,A2,A3,A4,A5;
	double B1,B2,B3,B4,B5;
	int C1,C2,C3,C4,C5;

	for (b = 0; b<8; b++)//dv
	{
		for (a = 0; a<1024; a++)//du
		{
			B1=(int(u*a+0.5)*2)*2.0/3329;
			B2=(int(u*a+0.5))  *2.0/3329;
			B3=2.0/3329;
			B4=(-int(u*a+0.5)) *2.0/3329;
			B5=(-(int(u*a+0.5))*2)*2.0/3329;

			if(int(B1+0.5)%2==0 && int(B2+0.5)%2==0 &&int(B3+0.5)%2==0 && int(B4+0.5)%2==0 && int(B5+0.5)%2==0)
			{
				A1=(int(v*b+0.5) + (int(u*a+0.5))*2)*2.0/3329;
				A2=(int(v*b+0.5) + int(u*a+0.5))  *2.0/3329;
				A3=(int(v*b+0.5))*2.0/3329;
				A4=(int(v*b+0.5) - int(u*a+0.5))  *2.0/3329;
				A5=(int(v*b+0.5) - (int(u*a+0.5))*2)*2.0/3329;

				C1=(int(A1+0.5))%2;
				C2=(int(A2+0.5))%2;
				C3=(int(A3+0.5))%2;
				C4=(int(A4+0.5))%2;
				C5=(int(A5+0.5))%2;

				if(C4<0)
				{
					C4=-C4;
				}
				if(C5<0)
				{
					C5=-C5;
				}

				//array1[C1*16+C2*8+C3*4+C4*2+C5]++;
				if(C1==1&&C2==1&&C3==0&&C4==0&&C5==0)
				{
					cout<<"a="<<a<<"b="<<b<<endl;
				}

			}

		}
	}

	/*
	for(i=0;i<32;i++)
	{
		if (array1[i]!=0)
		{
			cout<<"array1["<<i<<"]="<<array1[i]<<endl;
		}
	}
	*/

/*
	cin>>c;
	return 0;
}
*/

/*
int main()
{
	int i,j,k,t;

	bool flag;
	int array1[5][10]={0};
	int array2[5][3]={0};
	int w=0;
	int c,d,e,f,g,h;

	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			if((i+j)>=5)
			{
			array1[i][j]=1;
			}
		}
	}
	for(i=0;i<5;i++)
	{
		for(j=5;j<10;j++)
		{
			if(i<=(j-5))
			{
			array1[i][j]=1;
			}
		}
	}

	for (i=0;i<10;i++)
		for(j=i+1;j<10;j++)
			for(k=j+1;k<10;k++)

			{
				cout<<w++<<endl;
				flag=true;
				for(t=0;t<5;t++)
				{

					array2[t][0]=array1[t][i];
					array2[t][1]=array1[t][j];
					array2[t][2]=array1[t][k];

				}
				f=4;
				for(d=0;d<=3;d++)
				{	
					for(e=1;e<=f;e++)
					{
						if(array2[d][0]==array2[d+e][0] && array2[d][1]==array2[d+e][1] && array2[d][2]==array2[d+e][2])
						{ 
							flag=false;
							break;
						}

					}
					f=f-1;
				}

				if(flag)
				{
					for(g=0;g<5;g++)
					{
						for(h=0;h<3;h++)
						{
							cout<<array2[g][h];
						}
						cout<<endl;
					}

					cout<<"i="<<i<<"j="<<j<<"k="<<k<<endl;
					cin>>c;
				}
			}

}
*/


