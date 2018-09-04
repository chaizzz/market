#include <stdio.h>
#include "/usr/include/mysql/mysql.h"
#include <stdlib.h>


int main()
{
	int i, l, j, k, m;

	char n[2];

	printf("请输入密码：");
	scanf("%d", &l);

	if(l != 123456)
	{
		printf("密码错误\n");
		exit(1);
	}

	MYSQL mysql;
	mysql_init(&mysql);

	if(!mysql_real_connect(&mysql, "localhost", "xaz", "123456", "market", 0, NULL, 0))
	{
		fprintf(stderr, "Fail to connect to detabase: Error: %s\n", mysql_error(&mysql));
		exit(1);
	}

	mysql_query(&mysql, "set names utf8");

	printf("请输入操作人:\n1.经理\n2.入货员\n3.顾客\n");
	scanf("%d", &j);

	if(j == 1)
	{
		char z[7];

		const char* apassword = NULL;

		apassword =(char*)getpass("请输入密码:");

		
		char sql0[50];

		sprintf(sql0, "select * from Administration where ano = 1 and apassword = md5('%s')", apassword);

		//printf("%d\n", (mysql_query(&mysql, sql0)));

		if(!mysql_query(&mysql, sql0))
		{
			printf("密码错误！\n");
			exit(1);
		}	


		printf("是否对员工表进行修改？");
		scanf("%s", n);

first:
		if(n[0] == 'y')
		{
			int tno, tpassword;
			char tname[20];
			char o[2];

			printf("请输入需要的操作：\n1.添加员工\n2.删除员工\n3.修改员工信息\n4.查看员工信息\n5.退出系统\n");
			scanf("%d", &m);

			switch(m)
			{
				case 1:
					{
						char sql5[100];

						printf("员工编号：");
						scanf("%d", &tno);

						printf("员工名称：");
						scanf("%s", tname);

						printf("员工密码：");
						scanf("%d", &tpassword);

						sprintf(sql5, "insert into staff values(%d, '%s', %d)", tno, tname, tpassword);

						if(mysql_query(&mysql, sql5))
						{
							fprintf(stderr, "Fail to insert data to table student: Error: %s\n", mysql_error(&mysql));
						}
						else
						{
							if(mysql_affected_rows(&mysql) == 1)
							{
								printf("添加员工成功！\n");
							}
							if(mysql_affected_rows(&mysql) == 0)
							{
								printf("添加员工失败！\n");
							}
						}
						printf("是否继续操作？");
						scanf("%s", o);
						if('y' == o[0])
							goto first;
						else 
						break;
					}

				case 2:
					{
						char sql6[50];

						printf("请输入要删除的员工编号：");
						scanf("%d", &tno);

						sprintf(sql6, "delete from staff where tno = %d", tno);

						if(mysql_query(&mysql, sql6))
						{
							fprintf(stderr, "Fail to insert data to table student: Error: %s\n", mysql_error(&mysql));
						}
						else
						{
							if(mysql_affected_rows(&mysql) == 1)
								printf("删除员工成功！\n");
							if(mysql_affected_rows(&mysql) == 0)
								printf("删除员工失败！\n");
						}

						 printf("是否继续操作？");
                                                scanf("%s", o);
                                                if('y' == o[0])
                                                        goto first;
                                                else
						break;
					}
				case 3:
					{
						char sql7[50];
						char lie[10];
						int i, j;

						printf("请输入想修改的列：");
						scanf("%s", lie);

						printf("请输入新的值：");
						scanf("%d", &i);

						printf("请输入员工编号：");
						scanf("%d", &j);



						sprintf(sql7, "update staff set %s = %d where tno = %d", lie, i, j);


						if(mysql_query(&mysql, sql7))
						{
							fprintf(stderr, "Fail to insert data to table student: Error: %s\n", mysql_error(&mysql));
						}
						else
						{
							if(mysql_affected_rows(&mysql) == 1)
								printf("修改成功！\n");
							if(mysql_affected_rows(&mysql) == 0)
								printf("修改失败！\n");
						}

						printf("是否继续操作？");
                                                scanf("%s", o);
                                                if('y' == o[0])
                                                        goto first;
                                                else
						break;
					}
				case 4:
					{
						char sql8[50];

						printf("请输入要查询的员工编号：");
						scanf("%d", &tno);

						sprintf(sql8, "select * from staff where tno = %d", tno);

						if(mysql_query(&mysql, sql8))
						{
							fprintf(stderr, "Fail to insert data to table student: Error: %s\n", mysql_error(&mysql));
						}
						else
						{
							MYSQL_RES* res;

							res = mysql_store_result(&mysql);

							MYSQL_ROW row;

							while(row = mysql_fetch_row(res))
							{
								printf("%s %s %s\n", row[0], row[1], row[2]);
							}

							mysql_free_result(res);
						}

						printf("是否继续操作？");
                                                scanf("%s", o);
                                                if('y' == o[0])
                                                        goto first;
                                                else
						break;
	i			}
				case 5:
					{
						exit(1);
					}

			}
		}
	}


	if(j == 2)
	{
		char z[7];

		printf("请输入密码：");
		scanf("%s", z);

		if(mysql_query(&mysql, "select tpassword from staff"))
		{
			fprintf(stderr, "Fail to insert data to table student: Error: %s\n", mysql_error(&mysql));
		}
		else
		{
			MYSQL_RES* res;

			res = mysql_store_result(&mysql);

			MYSQL_ROW row;

			while(row = mysql_fetch_row(res))
			{
				if(z[0] != row[0][0] || z[1] != row[0][1] || z[2] != row[0][2] || z[3] != row[0][3] || z[4] != row[0][4] || z[5] != row[0][5])
				{
					printf("密码错误!\n");
					exit(1);
				}
			}

			mysql_free_result(res);
		}
	}

	switch(j)
	{

		int id, cost, price, profit, maintain;
		char name[20];
		char time[20];
		char o[2];

		second:
		case 1:
		{
			printf("请输入需要的操作：\n1.添加商品\n2.删除商品\n3.修改商品信息\n4.查看商品信息\n5.退出系统\n");
			scanf("%d", &i);

			switch(i)
			{
				case 1:
					{
						char sql1[100];

						printf("商品编号：");
						scanf("%d", &id);

						printf("商品名称：");
						scanf("%s", name);

						printf("成本：");
						scanf("%d", &cost);

						printf("售价：");
						scanf("%d", &price);

						printf("生产日期：");
						scanf("%s", &time);

						printf("保质期：");
						scanf("%d", &maintain);

						sprintf(sql1, "insert into market values(%d, '%s', %d, %d, %d, '%s', %d)", id, name, cost, price, price-cost, time, maintain);

						if(mysql_query(&mysql, sql1))
						{
							fprintf(stderr, "Fail to insert data to table student: Error: %s\n", mysql_error(&mysql));
						}
						else
						{
							if(mysql_affected_rows(&mysql) == 1)
							{
								printf("添加商品成功！\n");
							}
							if(mysql_affected_rows(&mysql) == 0)
							{
								printf("添加商品失败！\n");
							}
						}

						printf("是否继续操作？");
                                                scanf("%s", o);
                                                if('y' == o[0])
                                                        goto second;
                                                else

						break;
					}

				case 2:
					{
						char sql2[50];

						printf("请输入要删除的商品编号：");
						scanf("%d", &id);		

						sprintf(sql2, "delete from market where id = %d", id);

						if(mysql_query(&mysql, sql2))
						{
							fprintf(stderr, "Fail to insert data to table student: Error: %s\n", mysql_error(&mysql));
						}
						else
						{
							if(mysql_affected_rows(&mysql) == 1)
								printf("删除商品成功！\n");
							if(mysql_affected_rows(&mysql) == 0)
								printf("删除商品失败！\n");
						}
						printf("是否继续操作？");
                                                scanf("%s", o);
                                                if('y' == o[0])
                                                        goto first;
                                                else

						break;
					}
				case 3:
					{
						char sql3[50];
						char lie[10];
						int i, j;

						printf("请输入想修改的列：");
						scanf("%s", lie);

						printf("请输入新的值：");
						scanf("%d", &i);

						printf("请输入商品编号：");
						scanf("%d", &j);



						sprintf(sql3, "update market set %s = %d where id = %d", lie, i, j);


						if(mysql_query(&mysql, sql3))
						{
							fprintf(stderr, "Fail to insert data to table student: Error: %s\n", mysql_error(&mysql));
						}
						else
						{
							if(mysql_affected_rows(&mysql) == 1)
								printf("修改商品成功！\n");
							if(mysql_affected_rows(&mysql) == 0)
								printf("修改商品失败！\n");
						}
						mysql_query(&mysql, "update market set profit = (price-cost)");

						printf("是否继续操作？");
                                                scanf("%s", o);
                                                if('y' == o[0])
                                                        goto first;
                                                else
						break;
					}
				case 4:
					{
						char sql4[50];

						printf("请输入要查询的商品编号：");
						scanf("%d", &id);

						sprintf(sql4, "select * from market where id = %d", id);

						if(mysql_query(&mysql, sql4))
						{
							fprintf(stderr, "Fail to insert data to table student: Error: %s\n", mysql_error(&mysql));
						}
						else
						{
							MYSQL_RES* res;

							res = mysql_store_result(&mysql);

							MYSQL_ROW row;

							while(row = mysql_fetch_row(res))
							{
								printf("%s %s %s %s %s %s %s\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
							}

							mysql_free_result(res);
						}

						printf("是否继续操作？");
                                                scanf("%s", o);
                                                if('y' == o[0])
                                                        goto first;
                                                else
						break;
					}
				case 5:
					{
						exit(1);
					}

			}	

			mysql_close(&mysql);
			break;
		}

		third:
		case 2:
		{
			printf("请输入需要的操作：\n1.添加商品\n2.删除商品\n3.修改商品信息\n4.查看商品信息\n5.退出系统\n");
			scanf("%d", &i);

			int id, cost, price, profit, maintain;
			char o[2];
			char name[20];
			char time[20];
			switch(i)
			{
				case 1:
					{
						char sql1[100];

						printf("商品编号：");
						scanf("%d", &id);

						printf("商品名称：");
						scanf("%s", name);

						printf("成本：");
						scanf("%d", &cost);

						printf("售价：");
						scanf("%d", &price);

						printf("生产日期：");
						scanf("%s", &time);

						printf("保质期：");
						scanf("%d", &maintain);

						sprintf(sql1, "insert into market values(%d, '%s', %d, %d, %d, '%s', %d)", id, name, cost, price, price-cost, time, maintain);

						if(mysql_query(&mysql, sql1))
						{
							fprintf(stderr, "Fail to insert data to table student: Error: %s\n", mysql_error(&mysql));
						}
						else
						{
							if(mysql_affected_rows(&mysql) == 1)
							{
								printf("添加商品成功！\n");
							}
							if(mysql_affected_rows(&mysql) == 0)
							{
								printf("添加商品失败！\n");
							}
						}

						printf("是否继续操作？");
                                                scanf("%s", o);
                                                if('y' == o[0])
                                                        goto third;
                                                else
						break;
					}			
				case 2:
					{
						char sql2[50];

						printf("请输入要删除的商品编号：");
						scanf("%d", &id);

						sprintf(sql2, "delete from market where id = %d", id);

						if(mysql_query(&mysql, sql2))
						{
							fprintf(stderr, "Fail to insert data to table student: Error: %s\n", mysql_error(&mysql));
						}
						else
						{
							if(mysql_affected_rows(&mysql) == 1)
								printf("删除商品成功！\n");
							if(mysql_affected_rows(&mysql) == 0)
								printf("删除商品失败！\n");
						}

						printf("是否继续操作？");
                                                scanf("%s", o);
                                                if('y' == o[0])
                                                        goto third;
                                                else
						break;
					}
				case 3:
					{
						char sql3[50];
						char lie[10];
						int i, j;

						printf("请输入想修改的列：");
						scanf("%s", lie);

						printf("请输入新的值：");
						scanf("%d", &i);

						printf("请输入商品编号：");
						scanf("%d", &j);



						sprintf(sql3, "update market set %s = %d where id = %d", lie, i, j);


						if(mysql_query(&mysql, sql3))
						{
							fprintf(stderr, "Fail to insert data to table student: Error: %s\n", mysql_error(&mysql));
						}
						else
						{
							if(mysql_affected_rows(&mysql) == 1)
								printf("修改商品成功！\n");
							if(mysql_affected_rows(&mysql) == 0)
								printf("修改商品失败！\n");
						}
						mysql_query(&mysql, "update market set profit = (price-cost)");

						printf("是否继续操作？");
                                                scanf("%s", o);
                                                if('y' == o[0])
                                                        goto third;
                                                else
						break;
					}
				case 4:
					{
						char sql4[50];

						printf("请输入要查询的商品编号：");
						scanf("%d", &id);

						sprintf(sql4, "select * from market where id = %d", id);

						if(mysql_query(&mysql, sql4))
						{
							fprintf(stderr, "Fail to insert data to table student: Error: %s\n", mysql_error(&mysql));
						}
						else
						{
							MYSQL_RES* res;

							res = mysql_store_result(&mysql);

							MYSQL_ROW row;

							while(row = mysql_fetch_row(res))
							{
								printf("%s %s %s %s %s %s %s\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
							}

							mysql_free_result(res);
						}

						printf("是否继续操作？");
                                                scanf("%s", o);
                                                if('y' == o[0])
                                                        goto third;
                                                else
						break;
					}
				case 5:
					{
						exit(1);
					}

			}

			mysql_close(&mysql);
			break;
		}
		fourth:
		case 3:
		{
			char sql4[50];
			char o[2];

			printf("请输入要查询的商品名称：");
			scanf("%s", name);

			sprintf(sql4, "select id,name,price from market where name = '%s'", name);

			if(mysql_query(&mysql, sql4))
			{
				fprintf(stderr, "Fail to insert data to table student: Error: %s\n", mysql_error(&mysql));
			}
			else
			{
				MYSQL_RES* res;

				res = mysql_store_result(&mysql);

				MYSQL_ROW row;

				while(row = mysql_fetch_row(res))
				{
					printf("%s %s %s\n", row[0], row[1], row[2]);
				}

				mysql_free_result(res);
			}

			printf("是否继续查询商品？");
			scanf("%s", o);
			if('y' == o[0])
				goto fourth;
			else
			break;
		}
	}


return 0;

}
