/*
Our goal is to find as few (a,b) pairs so that bit strings corresponding to values of s_(i,j) are different. 
In other words, We need to find as few columns as possible from a 7-by-2^{(d_u + d_v)} matrix so that each
row of the selected matrix is different. There are at most 2^7 different columns in the matrix and many (a,b) 
pairs correspond to the same column. By transforming each bit string into an integer, we can find these different 
columns and each column corresponds to many (a, b) pairs. Thus, a large matrix is reduced into a small matrix 
and we will choose as few columns as possible from this small matrix. Since s_(i,j) has 7 possible values, 
at least 3 columns are needed. However, by searching, we found that there are no 3 columns that meet the 
conditions, then we try to choose 4 columns.
*/

#include<iostream>
#include <stdio.h>
#include <math.h>


#include <stdint.h>
#include <Windows.h>
using namespace std;



int main()
{
	//²ÎÊýFireSaber
	int n=256;
	int eq=13;
	int q=8192;//q=2^eq
	int ep=10;
	int p=1024;//p=2^ep



	int et=6;
	int t=64;//2^et
	int Mpt=16;//Mpt=2^(ep-et)=2^4
	int h2=252;//h2=256-2^(ep-et-1)+4
	int eta=3;
	int pv=7;//2*eta+1 possible values of S_t
	int mpv=128;//2^pv
	int array1[7]={0};//record m_j correspongding to S_t,j!=0
	int array2[7]={0};//recover m_0 correspongding to S_t
	int *array3;
    array3=(int*)calloc(128,sizeof(int));//2^pv,find out the differnt bit strings and record how many (a,b) paris correspond to each bit string in array3
	int *array4;
    array4=(int*)calloc(128,sizeof(int));//2^pv,record the differnt bit strings in array4 and transform the bit string into integer and record it in array4
	int count=0;//the number of the differnt bit strings,count=10
	int array5[7][10]={0};//7 is the possible values of S_t and 10 is the number of the differnt bit strings
	int array6[7][4]={0};//choose 4 columns  from this array5, so that each row of the selected matrix is different
	int column=4;////choose 4 columns  from this array5



	int a,b;//a,b
	int st;//S_t
	int temp;
	int c,d,e,f,g,h,l,m,o,r,s,u,v;
	bool flag;
	int sum;
	int mula;
	int i,j,k,tt;
	
	int controloutput=0;//
	int number=0;//the number of all choices satisfying the conditions
	int number_better=0;//the number of the choices to get better results 
	int i_output1,j_output1,k_output1,l_output1,m_output1,o_output1;//output the first choice
	int i_output2,j_output2,k_output2,l_output2;//output the first one of better choices
	int count_i=0,count_j=0,count_k=0,count_l=0,count_m=0,count_o=0;// count the number of (a, b) pairs corresponding to each column in the output choice
	bool flag_i=true,flag_j=true,flag_k=true,flag_l=true,flag_m=true,flag_o=true;

	//a in {0,...,(2^et)-1},b in {0,...,(2^ep)-1}
	for (b = 0; b<p; b++)
	{
		for (a = 0; a<t; a++)
		{
			flag=true;
			for(st=0;st<pv;st++)//S_t in {-3,-2,...,2,3}
			{
				array1[st]=(b*(st-eta)+h2)%p;//m_j,j!=0
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

			if(flag)//m_j=0,j!=0
			{
				for(st=0;st<pv;st++)//S_t in {-3,-2,...,2,3}
				{
					array2[st]=(b*(st-eta)-a*Mpt+h2)%p;//m_0
					if(array1[st]<0)
					{
						array2[st]=array2[st]+p;
					}
					array2[st]=array2[st]>>(ep-1);
				}
			}
			
		   //for a (a, b) pair, m_0's values constitutes a 5-bit string when S_t takes 7 different values,
		   //since the length of the bit string is 7, it has 2^7 possibles and a large number of (a, b) pairs corresponds to the same bit string 
           //convert the bit strings into integers for the convenience of finding the same bit string 
			sum=0;
			mula=1;
			for(st=0;st<pv;st++)//S_t has 7 possible values and the length of the bit string is 7
			{
				sum=sum+array2[st]*mula;

				mula=mula*2;
			}
			array3[sum]++;//find out the differnt bit strings and count the number of each bit string (integer)

		}
	}


	//count the number of different bit strings and recored the differnt bit strings (integers) in array4
	j=0;
	for(i=0;i<mpv;i++)//since the length of the bit string is 7, it has 2^7 possibles
	{
		if (array3[i]!=0)
		{
			array4[j]=i;
			count++;
			j++;
			//cout<<"array3["<<i<<"]="<<array3[i]<<endl;
		}

	}
	cout<<"there are "<<count<<" different bit strings and they are: "<<endl;//count=10

	for (j=0;j<count;j++)//count=10
	{
		//cout<<"array4["<<j<<"]"<<array4[j]<<endl;
	}

	//after finding out the differnt bit strings and output them 
	for (j=0;j<count;j++)//count=10
	{
		temp=array4[j];
		array5[0][j]=temp%2;
		for(i=1;i<pv;i++)//7 possible values
		{
			temp=temp/2;
			array5[i][j]=temp%2;
		}
	}
	// the each column of array5 is the bit string
	for (j=0;j<count;j++)//count=10
	{
		cout<<"array5["<<j<<"]="<<array4[j]<<"=";

		for(i=0;i<pv;i++)//7 possible values
		{
			cout<<array5[i][j];
		}
		cout<<endl;
	}
	//cout<<"since the bit strings corresponding to -1 and 0 are all the same, S_t=-1 or 0 can't be distinguished."<<endl;
	cout<<endl;

   //Remove a large number of duplicates and we get a 7-by-count matrix.
	//This matrix is much smaller than the previous 7-by-(d_v*d_u) matrix
   //We choose as few columns as possible from this matrix, so that each row of the selected matrix is different 
	//Since S_t has 7 possible values, at least 3 columns are needed ,but there are no 3 columns that meet the conditions
	//In particualr, we choose 4 columns
	for (i=0;i<count;i++)//count=10
		for(j=i+1;j<count;j++)//count=10
			for(k=j+1;k<count;k++)//count=10	
				for(l=k+1;l<count;l++)//count=10	
					
				{
					flag=true;
					for(tt=0;tt<pv;tt++)//7 possible values
					{
						array6[tt][0]=array5[tt][i];
						array6[tt][1]=array5[tt][j];
						array6[tt][2]=array5[tt][k];
						array6[tt][3]=array5[tt][l];
					}

					f=pv-1;//7 possible values
					for(d=0;d<pv;d++)//7 possible values
					{	
						for(e=1;e<=f;e++)
						{
							if(array6[d][0]==array6[d+e][0] && array6[d][1]==array6[d+e][1] && array6[d][2]==array6[d+e][2] && array6[d][3]==array6[d+e][3])
							{
								flag=false;
								break;
							}

						}
						f=f-1;
					}

					if(flag)
					{
						number++;//record all the choices that meet the conditions
						//if(controloutput==0)//only output the first choice
						//{
						    //there are 5 choices and we output all the choices
						    cout<<"We choose 4 columns so that each row of the selected matrix is different"<<endl;
							cout<<"the choice is: "<<endl;
							controloutput++;
							for(g=0;g<pv;g++)//7 possible values
							{
								for(h=0;h<column;h++)//try to distinguish each coefficient of s using 4 queries
								{
									cout<<array6[g][h];
								}
								cout<<endl;
							}

							cout<<"they are taken from columns"<<" "<<i<<" "<<j<<" "<<k<<" "<<l<<" of the  array5"<<endl;
							//cout<<"i="<<i<<", j="<<j<<", k="<<k<<", l="<<l<<endl;
							cout<<" "<<endl;

							//record the 4 columns in order to find the corresponding (a,b) pair next 
							i_output1=i;
							j_output1=j;
							k_output1=k;
							l_output1=l;
							//o_output1=o;
							//m_output1=m;
						//}
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
				cout<<"there are "<<number<<" choices,";
				cout<<"in order to output the first choice, as shown above,"<<endl;
				for (b = 0; b<p; b++)
				{
					for (a = 0; a<t; a++)
					{
						flag=true;
						for(st=0;st<pv;st++)
						{
							array1[st]=(b*(st-eta)+h2)%p;
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
							for(st=0;st<pv;st++)
							{
								array2[st]=(b*(st-eta)-a*Mpt+h2)%p;
								if(array1[st]<0)
								{
									array2[st]=array2[st]+p;
								}
								array2[st]=array2[st]>>(ep-1);
							}
						}

						
						sum=0;
						mula=1;
						for(st=0;st<pv;st++)//7 possible values
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
						//if(sum==array4[m_output1]){count_m++;if (flag_m){flag_m=false;cout<<"the 5td query is "<<"a="<<a<<", b="<<b<<endl;}}
						//if(sum==array4[o_output1]){count_o++;if (flag_o){flag_o=false;cout<<"the 6th query is "<<"a="<<a<<", b="<<b<<endl;}}
					}
				}

				cout<<"the 1st query has "<<count_i<<" (a,b) pairs and we take the first one"<<endl;
				cout<<"the 2nd query has "<<count_j<<" (a,b) pairs and we take the first one"<<endl;
				cout<<"the 3rd query has "<<count_k<<" (a,b) pairs and we take the first one"<<endl;
				cout<<"the 4th query has "<<count_l<<" (a,b) pairs and we take the first one"<<endl;
				//cout<<"the 5rd query has "<<count_m<<" (a,b) pairs and we take the first one"<<endl;
				//cout<<"the 6th query has "<<count_o<<" (a,b) pairs and we take the first one"<<endl;
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
