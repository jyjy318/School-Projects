#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct MEMORY
{
	int page_num;
	int reference_bit;
	int dirty_bit;

};

struct MEMORY memory[4];

struct PAGE
{
	int memory_location;
	int valid_bit;
};

struct PAGE page[200000];

int PageFaultCount = 0;
int DiskWriteCount = 0;
int DiskHeadDistance = 0;



int main(int argc, char*argv[])
{
	int memory_size = atoi(argv[1]);
	FILE* input_file = fopen("a.txt", "r");
	struct MEMORY* memory = (struct MEMORY*)malloc(memory_size * sizeof(struct MEMORY));

	if (input_file == NULL)
	{
		printf("파일을 여는데 실패하였습니다 ");
		exit(0);
	}
	else
	{
		printf("");
	}

	for (int i = 0; i < memory_size; i++)
	{
		memory[i].page_num = -1;
		memory[i].reference_bit = 0;
		memory[i].dirty_bit = 0;
	}

	for (int i = 0; i < 200000; i++)
	{
		page[i].memory_location = -1;
		page[i].valid_bit = 0;
	}

	int pg = 0;
	int op = 0;
	int diskHeadLocation = 0;
	int nextPageFaultLocation = 0;
	int goToLocation = 0;
	int distance = 0;

	while (!feof(input_file))
	{
		fscanf(input_file, "%d %d", &pg, &op);

		if (page[pg].valid_bit == 1)
		{
			for (int i = 0; i < memory_size; i++)
			{
				if (memory[i].page_num == pg)
				{
					memory[i].reference_bit = 1;
					if (memory[i].dirty_bit == 0 && op == 1)
					{
						memory[i].dirty_bit = 1;
					}
					break;
				}
			}
		}
		else
		{

			PageFaultCount++;



			int i = nextPageFaultLocation;

			while (true)
			{
				if (memory[i].reference_bit == 1)
				{
					memory[i].reference_bit = 0;
				}
				else
				{


					if (memory[i].page_num != -1)
					{
						page[memory[i].page_num].valid_bit = 0;
						page[memory[i].page_num].memory_location = -1;
					}

					if (memory[i].dirty_bit == 1)
					{

						DiskWriteCount++;


						goToLocation = memory[i].page_num / 1000;
						distance = abs(goToLocation - diskHeadLocation);
						DiskHeadDistance += distance;
						diskHeadLocation = goToLocation;
					}


					goToLocation = pg / 1000;
					distance = abs(goToLocation - diskHeadLocation);
					DiskHeadDistance += distance;
					diskHeadLocation = goToLocation;


					page[pg].memory_location = i;
					page[pg].valid_bit = 1;

					memory[i].page_num = pg;
					memory[i].reference_bit = 0;
					memory[i].dirty_bit = op;

					nextPageFaultLocation = i + 1;
					nextPageFaultLocation %= memory_size;



					break;
				}

				i++;
				i %= memory_size;
			}


		}
	}

	printf("%d ", PageFaultCount);
	printf("%d ", DiskWriteCount);
	printf("%d ", DiskHeadDistance);
}