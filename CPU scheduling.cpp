#include <stdio.h>

void fcfs();
void sjf();
void priority();
void rr();

int main()
{
	int num;

	while (1)
	{
		printf("1.FCFS  2.SJF  3.PRIORITY  4.RR  5.종료\n");
		printf("선택 : ");
		scanf_s("%d", &num);

		if (num == 1)
			fcfs();
		else if (num == 2)
			sjf();
		else if (num == 3)
			priority();
		else if (num == 4)
			rr();
		else if (num == 5)
		{
			printf("종료합니다.\n");
			break;
		}
		else
			printf("다시 입력하세요\n");
	}
}

void fcfs()
{
	int arrivalTime[10], burstTime[10], burstTime_copy[10];
	int waitTime[10], turnaroundTime[10], completeTime[10];
	int i, j, n, burstSum;
	double Average_waitTime = 0, Average_turnaroundTime = 0;

	printf("process의 개수를 입력하세요: ");
	scanf_s("%d", &n) >> n;

	for (i = 0; i < n; i++)
	{
		printf("process%d의 arrivalTime을 입력하세요 : ", i + 1);
		scanf_s("%d", &arrivalTime[i]);
	}
	for (i = 0; i < n; i++)
	{
		printf("process%d의 burstTime을 입력하세요 : ", i + 1);
		scanf_s("%d", &burstTime[i]);
	}
	for (i = 0; i < n; i++)
		burstTime_copy[i] = burstTime[i];

	turnaroundTime[0] = burstTime[0] + arrivalTime[0];
	waitTime[0] = arrivalTime[0];
	completeTime[0] = burstTime[0];
	burstSum = burstTime[0];

	for (i = 1; i < n; i++)
	{
		if (burstSum < arrivalTime[i]) // arrivaltime이 busrtSum 보다 클때
		{
			turnaroundTime[i] = burstTime[i] + arrivalTime[i];
			burstSum = burstTime[i] + arrivalTime[i];
		}
		else // 정상적인 형태일 때
		{
			waitTime[i] = burstSum - arrivalTime[i];
			burstSum += burstTime[i];
			turnaroundTime[i] = burstSum - arrivalTime[i];
			completeTime[i] = burstSum;
		}
	}

	printf("\nProcess\t burst - time\t arrival - time\t wait - time\t processing - time\t turnaround - time\t complete - time\n");
	for (i = 0; i < n; i++)
	{
		printf("p%d \t %d \t\t %d \t\t %d \t\t %d ~ %d -> %d \t\t %d \t\t\t %d\n", i + 1, burstTime_copy[i], arrivalTime[i],
			waitTime[i], completeTime[i] - burstTime_copy[i], completeTime[i], burstTime_copy[i], turnaroundTime[i], completeTime[i]);
		Average_waitTime = Average_waitTime + waitTime[i];
		Average_turnaroundTime = Average_turnaroundTime + turnaroundTime[i];
	}
	printf("\nAverage waitingTime = %lf \n", Average_waitTime / n);
	printf("Average turnaroundTime = %lf\n", Average_turnaroundTime / n);
	printf("\n");
}

void sjf()
{
	int arrivalTime[10], burstTime[10], burstTime_copy[10];
	int waitTime[10], turnaroundTime[10], completeTime[10];
	int i, j, n, min, time, end;
	int burstSum = 0, tmp = -1, count = 0;
	double Average_waitTime = 0, Average_turnaroundTime = 0;

	printf("process의 개수를 입력하세요: ");
	scanf_s("%d", &n) >> n;


	for (i = 0; i < n; i++)
	{
		printf("process%d의 arrivalTime을 입력하세요 : ", i + 1);
		scanf_s("%d", &arrivalTime[i]);
	}
	for (i = 0; i < n; i++)
	{
		printf("process%d의 burstTime을 입력하세요 : ", i + 1);
		scanf_s("%d", &burstTime[i]);
	}
	for (i = 0; i < n; i++)
	{
		burstTime_copy[i] = burstTime[i];
		burstSum += burstTime[i];
	}

	burstTime[9] = 100;

	printf("\nprocessing - time\n");

	for (time = 1; count != n; time++)
	{
		min = 9;
		for (i = 0; i < n; i++)
		{
			if (arrivalTime[i] < time && burstTime[i] < burstTime[min] && burstTime[i] > 0)
				min = i;
		}
		if (tmp != min)
		{
			printf("p%d(%d) ~ ", min + 1, time - 1);
		}

		burstTime[min]--;
		tmp = min;

		if (burstTime[min] == 0)
		{
			count++;
			end = time;
			completeTime[min] = end;
			waitTime[min] = end - arrivalTime[min] - burstTime_copy[min];
			turnaroundTime[min] = end - arrivalTime[min];
		}
	}
	printf("(%d)\n", burstSum);
	printf("\nProcess\t burst - time\t arrival - time\t wait - time\t turnaround - time\t complete - time\n");
	for (i = 0; i < n; i++)
	{
		printf("p%d \t %d \t\t %d \t\t %d \t\t %d \t\t\t %d\n", i + 1, burstTime_copy[i], arrivalTime[i], waitTime[i], turnaroundTime[i], completeTime[i]);
		Average_waitTime = Average_waitTime + waitTime[i];
		Average_turnaroundTime = Average_turnaroundTime + turnaroundTime[i];
	}
	printf("\nAverage waitingTime = %lf\n", Average_waitTime / n);
	printf("Average turnaroundTime = %lf\n", Average_turnaroundTime / n);
	printf("\n");
}


void priority()
{
	int arrivalTime[10], burstTime[10], burstTime_copy[10];
	int waitTime[10], turnaroundTime[10], completeTime[10], priority[10];
	int i, j, n, min, time, end;
	int burstSum = 0, tmp = -1, count = 0;
	double Average_waitTime = 0, Average_turnaroundTime = 0;

	printf("process의 개수를 입력하세요: ");
	scanf_s("%d", &n) >> n;

	for (i = 0; i < n; i++)
	{
		printf("process%d의 arrivalTime을 입력하세요 : ", i + 1);
		scanf_s("%d", &arrivalTime[i]);
	}
	for (i = 0; i < n; i++)
	{
		printf("process%d의 burstTime을 입력하세요 : ", i + 1);
		scanf_s("%d", &burstTime[i]);
	}
	for (i = 0; i < n; i++)
	{
		printf("process%d의 priority을 입력하세요 : ", i + 1);
		scanf_s("%d", &priority[i]);
	}
	for (i = 0; i < n; i++)
	{
		burstTime_copy[i] = burstTime[i];
		burstSum += burstTime[i];
	}

	priority[9] = 100;

	printf("\nprocessing - time\n");

	for (time = 1; count != n; time++)
	{
		min = 9;
		for (i = 0; i < n; i++)
		{
			if (arrivalTime[i] < time && priority[i] < priority[min] && burstTime[i] > 0)
				min = i;
		}

		if (tmp != min)
		{
			printf("p%d(%d) ~ ", min + 1, time - 1);
		}

		burstTime[min]--;
		tmp = min;

		if (burstTime[min] == 0)
		{
			count++;
			end = time;
			completeTime[min] = end;
			waitTime[min] = end - arrivalTime[min] - burstTime_copy[min];
			turnaroundTime[min] = end - arrivalTime[min];
		}
	}
	printf("(%d)\n", burstSum);
	printf("\nProcess\t burst - time\t arrival - time\t priority\t wait - time\t turnaround - time\t complete - time\n");
	for (i = 0; i < n; i++)
	{
		printf("p%d \t %d \t\t %d \t\t %d \t\t %d \t\t %d \t\t\t %d\n", i + 1, burstTime_copy[i], arrivalTime[i], priority[i], waitTime[i], turnaroundTime[i], completeTime[i]);
		Average_waitTime = Average_waitTime + waitTime[i];
		Average_turnaroundTime = Average_turnaroundTime + turnaroundTime[i];
	}
	printf("\nAverage waitingTime = %lf\n", Average_waitTime / n);
	printf("Average turnaroundTime = %lf\n", Average_turnaroundTime / n);
	printf("\n");
}


void rr()
{
	int arrivalTime[10], burstTime[10], burstTime_copy[10];
	int waitTime[10], turnaroundTime[10], completeTime[10];
	int i, j, n, min, end, quantum;
	int burstSum = 0, time = 0, count = 0;
	double Average_waitTime = 0, Average_turnaroundTime = 0;

	printf("process의 개수를 입력하세요: ");
	scanf_s("%d", &n) >> n;
	for (i = 0; i < n; i++)
	{
		printf("process%d의 arrivalTime을 입력하세요 : ", i + 1);
		scanf_s("%d", &arrivalTime[i]);
	}
	for (i = 0; i < n; i++)
	{
		printf("process%d의 burstTime을 입력하세요 : ", i + 1);
		scanf_s("%d", &burstTime[i]);
	}
	printf("quantum을 입력하세요 : ");
	scanf_s("%d", &quantum);

	for (i = 0; i < n; i++)
	{
		burstTime_copy[i] = burstTime[i];
		burstSum += burstTime[i];
	}

	printf("\nprocessing - time\n");
	while (count != n)
	{
		for (i = 0; i < n; i++)
		{
			if (arrivalTime[i] <= time && burstTime[i] > 0)
			{
				printf("p%d(%d) ~ ", i + 1, time);
				for (j = 0; j < quantum; j++)
				{
					time++;
					burstTime[i]--;

					if (burstTime[i] == 0)
					{
						count++;
						completeTime[i] = time;
						waitTime[i] = time - arrivalTime[i] - burstTime_copy[i];
						turnaroundTime[i] = time - arrivalTime[i];
						break;
					}
				}
			}
		}
	}
	printf("(%d)\n", burstSum);
	printf("\nProcess\t burst - time\t arrival - time\t wait - time\t turnaround - time\t complete - time\n");
	for (i = 0; i < n; i++)
	{
		printf("p%d \t %d \t\t %d \t\t %d \t\t %d \t\t\t %d\n", i + 1, burstTime_copy[i], arrivalTime[i], waitTime[i], turnaroundTime[i], completeTime[i]);
		Average_waitTime = Average_waitTime + waitTime[i];
		Average_turnaroundTime = Average_turnaroundTime + turnaroundTime[i];
	}
	printf("\nAverage waitingTime = %lf\n", Average_waitTime / n);
	printf("Average turnaroundTime = %lf\n", Average_turnaroundTime / n);
	printf("\n");
}