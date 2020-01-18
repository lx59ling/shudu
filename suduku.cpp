#include<cstdio>
#include<cstdlib>
#include<iostream>
#include <fstream>

#include"perm.h"

using namespace std;

int* result[1000005];   //用于存放指向 存放数独终局数据数组 的指针

class sudo
{
private:
	int sudo_map[9][9];
	int count;
	int num;
public:
	sudo() {};
	sudo(int n)
	{
		count = 0;
		num = n;
	}
	void creat_End();
	void solve_Que();
	void write_to_file();
};

void sudo::creat_End()
{

	int first_line[9] = { 5,1,2,3,4,6,7,8,9 };   //数独模型第一行的某一种情况，第一个数：(6+8)%9+1=5 

	int row[8] = { 1,2,3,4,5,6,7,8 };    //进行行变化对应行的下标		

	int arr_change[8] = { 3,6,1,4,7,2,5,8 };		//由第一行的数分别向左移动 3、6、1、4、7、2、5、8 可以得到一个完整的数独终局

	do
	{
		for (int k = 0; k < 9; k++)   //为第一行赋值
			this->sudo_map[0][k] = first_line[k];

		//根据map的关系和第一行的某个排列生成其他行，得到一个数独终局的模板
		for (int i = 1; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
				this->sudo_map[i][j] = first_line[(arr_change[i - 1] + j) % 9];		//分别将first_line进行不同程度移位后的行赋给后续的行
		}

		do
		{
			do 
			{
				do
				{
					for (int j = 0; j < 9; j++)
					{

					}

					//将产生的矩阵存好
					int* new_sudo_map = (int *)malloc(81 * sizeof(int));

					for (int k = 0; k < 9; k++)   //为第一行赋值
						new_sudo_map[k] = first_line[k];

					for (int i = 1; i < 9; i++)
						for (int j = 0; j < 9; j++)
							new_sudo_map[i * 9 + j] = this->sudo_map[row[i-1]][j];  //将数独终局存入一个一维数组中，方便输出

					result[this->count] = new_sudo_map;
					this->count++;

					if (this->count == this->num)   //终局数达到要求了
						return;

				}while(Perm(row+5,row+7));			//对第7、8、9行进行排列

			} while (Perm(row+2, row+4));		//对第4、5、6行进行排列

		} while (Perm(row, row+1));		//对第2、3行进行排列

	} while (Perm(first_line + 1, first_line + 8));     //每对第一行的后8位进行排列后便据此生成一个新的数独终局模板 

	return ;
}

void sudo::solve_Que()
{
	1;
}

void sudo::write_to_file()
{
	ofstream fp;

	fp.open("sudoku.txt",ios::app);
	
	if (!fp) 
	{
		cout << "打开文件失败" << endl;
		return ;
	}

	for (int i = 0; i < this->num; i++)
	{
		for (int j = 0; j < 81; j++)
		{
			fp << *(result[i]+j);
			
			if (j % 9 == 8)
			{
				fp << endl;
				continue;
			}

			fp << " ";
		}

		if(i < this->num -1)
		fp << endl;

	}

	fp.close();
}

int main(int argc, char const *argv[])
{

	
	if (argc != 3 ) //未按照标准格式输入 
	{
		printf("请输入正确的格式\n");
		printf("如: sudo.exe -c 100\n");
		printf("    sudo.exe -s absolute_path_of_puzzlefile\n");
		
		return 0;
	}

	if (strcmp(argv[1], "-c") == 0)  //-c输出数独终局
	{
		int num = atoi(argv[2]);

		if (num <= 0 && num > 1000000)	//n不按要求输入时，报错
		{
			printf("请输入正确的格式\n");
			printf("如: sudo.exe -c 100\n");
			exit(0);
		}

		else
		{
			sudo sudo1(num);
			
			sudo1.creat_End();
			sudo1.write_to_file();

			return 0;
		}
		
	}

	if (strcmp(argv[1], "-s") == 0)  //-s求解数独问题
	{
		sudo sudo2;

		sudo2.solve_Que();
	}

	/*

	sudo sudo1(10);

	sudo1.creat_End();
	sudo1.write_to_file();

	

	return 0;
	*/

}
