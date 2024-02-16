#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>

void delay(float number_of_seconds)
{
	int milli_seconds = 1000 * number_of_seconds;
	clock_t start_time = clock();
	while (clock() < start_time + milli_seconds);
}

int findRandom()
{
  int num = rand() % 2;
  return num;
}

void colorq()
{
    printf("\x1b[32m");
}

void colorm()
{
    printf("\x1b[35m");
}

void color()
{
    printf("\033[0;36m");
}

void colorr()
{
    printf("\x1b[31m");
}

void reset()
{
    printf("\033[0m");
}

bool isOk(int arr[20][20], int x, int y, int ex, int ey)
{
    if(x<=ex && y<=ey && arr[x][y]==1)
    {
        return true;
    }
    return false;
}

bool ratMap(int arr[20][20], int x, int y, int ex, int ey, int solMap[20][20])
{
    if((x==ex) && (y==ey))
    {
        solMap[x][y]=1;
        return true;
    }

    if(isOk(arr,x,y,ex,ey))
    {
        solMap[x][y]=1;
        if(ratMap(arr,x+1,y,ex,ey,solMap))
        {
            return true;
        }
        if(ratMap(arr,x,y+1,ex,ey,solMap))
        {
            return true;
        }
        solMap[x][y]=0;
        return false;
    }
    return false;
}

bool ratMapProgress(int arr[20][20], int x, int y, int ex, int ey, int solMap[20][20], int n)
{
	int i,j;
    for( i=0; i<n; i++)
    {
        for( j=0; j<n; j++)
        {
            if(solMap[i][j]==1)
            {
                colorm();
                printf("  %d",solMap[i][j]);
                if(n<=5)
                    delay(0.1);
                else if(n<=10)
                    delay(0.05);
                else
                    delay(0.001);
                reset();
            }
            else
            {
                printf("  %d",solMap[i][j]);
            }
        }
        printf("\n");
    }
	printf("\nSearching...\b\b\b\b\b\b\b\b\b\b\b\b");
    for( i=0; i<n+1; i++)
    {
        printf("\033[A");
    }
    if((x==ex) && (y==ey))
    {
        solMap[x][y]=1;
        return true;
    }
    if(isOk(arr,x,y,ex,ey))
    {
        solMap[x][y]=1;
        if(ratMapProgress(arr,x+1,y,ex,ey,solMap,n))
        {
            return true;
        }
        if(ratMapProgress(arr,x,y+1,ex,ey,solMap,n))
        {
            return true;
        }
        solMap[x][y]=0;
        return false;
    }
    return false;
}

int main()
{
    FILE *f;
    int n, ch, temp,i,j;
    int sx, sy;
    int ex, ey;
    int arr[20][20], solMap[20][20];
    bool flag = false;

    f = fopen("Maze.txt","a");

    if(f == NULL)
    {
        printf("\nFile error encountered!!!\n");
    }

    time_t t;
    time(&t);

    fprintf(f,"\n>>%s", ctime(&t));

    printf("\nBINARY MATRIX MAZE SOLVER!!!");
    printf("\n\nEnter the size of the binary matrix maze (max 20): ");
    fprintf(f,"Enter the size of the binary matrix maze (max 20): ");
    scanf("%d",&n);
    fprintf(f,"%d",n);


    printf("\nEnter 0 for default (1,1)/(%d,%d) & 1 for user start/end coordinates: ",n,n);
    fprintf(f,"\nEnter 0 for default (1,1)/(%d,%d) & 1 for user start/end coordinates: ",n,n);
    scanf("%d",&temp);
    fprintf(f,"%d",temp);

    if(temp)
    {
        printf("\nEnter the starting coordinate: ");
        fprintf(f,"\nEnter the starting coordinate: ");
        scanf("%d %d",&sx, &sy);
        fprintf(f,"%d,%d",sx, sy);
        sx--;
        sy--;

        printf("\nEnter the ending coordinate: ");
        fprintf(f,"\nEnter the ending coordinate: ");
        scanf("%d %d",&ex, &ey);
        fprintf(f,"%d,%d",ex, ey);
        ex--;
        ey--;
    }
    else
    {
        sx = 0;
        sy = 0;
        ex = n-1;
        ey = n-1;
    }

    printf("\nEnter 1 for user input maze and 2 for random maze: ");
    fprintf(f,"\nEnter 1 for user input maze and 2 for random maze: ");
    scanf("%d",&ch);
    fprintf(f,"%d",ch);

    if(ch==1)
    {
        fprintf(f,"\n\nInput Matrix is:\n\n");
        printf("\nEnter your matrix:\n\n");
        for( i=0;i<n;i++)
        {
            for( j=0;j<n;j++)
            {
                scanf("%d",&arr[i][j]);
                fprintf(f,"  %d",arr[i][j]);
            }
            fprintf(f,"\n");
        }
        for( i=0;i<n;i++)
        {
            for( j=0;j<n;j++)
            {
                solMap[i][j]=0;
            }
        }

        printf("\nIf the rat moves right and down only, the path of the rat may be\n (S:(%d,%d)|E:(%d,%d)):\n\n",sx+1,sy+1,ex+1,ey+1);
        fprintf(f,"\nIf the rat moves right and down only, the path of the rat may be\n (S:(%d,%d)|E:(%d,%d)):\n\n",sx+1,sy+1,ex+1,ey+1);
        if(ratMap(arr,sx,sy,ex,ey,solMap))
        {
            for( i=0;i<n;i++)
            {
                for( j=0;j<n;j++)
                {
                    solMap[i][j]=0;
                }
            }
            ratMapProgress(arr,sx,sy,ex,ey,solMap,n);
            for( i=0;i<n;i++)
            {
                for( j=0;j<n;j++)
                {
                    if(solMap[i][j]==1)
                    {
                        if((i==sx && j==sy) || (i==ex && j==ey))
                        {
                            colorr();
                            delay(0.1);
                            printf("  %d",solMap[i][j]);
                            delay(0.1);
                            reset();
                        }
                        else
                        {
                            color();
                            delay(0.1);
                            printf("  %d",solMap[i][j]);
                            delay(0.1);
                            reset();
                        }
                    }
                    else
                    {
                        printf("  %d",solMap[i][j]);
                    }
                    fprintf(f,"  %d",solMap[i][j]);
                }
                printf("\n");
                fprintf(f,"\n");
            }
			printf("\nPath found!!!");
		    fprintf(f,"\nPath found!!!");
			printf("\n\nGame data sucessfully stored in Maze.txt!!!");
            printf("\n\n");
            fprintf(f,"\n\n");
        }
        else
        {
            printf("No valid path exist!!!\n\n");
            fprintf(f,"No valid path exist!!!\n\n");
        }
    }

    else if(ch==2)
    {
        for( i=0; i<n; i++)
        {
            for( j=0; j<n; j++)
            {
                arr[i][j] = 0;
            }
        }
        srand(time(0));
        for( i=0; i<ex+1; i++)
        {
            for( j=0; j<ey+1; j++)
            {
                if(i == sx && j == sy)
                {
                    arr[i][j] = 1;
                    flag = true;
                }
                if(flag)
                {
                    if(i == ex && j == ey)
                    {
                        arr[i][j] = 1;
                        break;
                    }
                    temp = findRandom();
                    if(temp == 0)
                    {
                        if(i!=(ex))
                        {
                            arr[i+1][j]=1;
                            i++;
                            j--;
                            continue;
                        }
                        else
                        {
                            arr[i][j+1]=1;
                            j--;
                            continue;
                        }
                    }
                    if(temp == 1)
                    {
                        if(j!=(ey))
                        {
                            arr[i][j+1]=1;
                            continue;
                        }
                        else
                        {
                            arr[i+1][j]=1;
                            j--;
                            continue;
                        }
                    }
                }
            }
        }

        for( i=0;i<n;i++)
        {
            for( j=0;j<n;j++)
            {
                if(arr[i][j] == 1)
                    continue;
                else
                    arr[i][j] = findRandom();
            }
        }

        printf("\nGenerated Random Maze:\n\n");
        fprintf(f,"\n\nGenerated Random Maze:\n\n");
        for( i=0; i<n; i++)
        {
            for( j=0; j<n; j++)
            {
                if(arr[i][j]==1)
                {
                    colorq();
                    printf("  %d",arr[i][j]);
                    delay(0.1);
                    reset();
                }
                else
                {
                    printf("  %d",arr[i][j]);
                    delay(0.01);
                }
                fprintf(f,"  %d",arr[i][j]);
            }
            printf("\n");
            fprintf(f,"\n");
        }

        for( i=0;i<n;i++)
        {
            for( j=0;j<n;j++)
            {
                solMap[i][j]=0;
            }
        }

        printf("\nIf the rat moves right and down only, the path of the rat may be\n (S:(%d,%d)|E:(%d,%d)):\n\n",sx+1,sy+1,ex+1,ey+1);
        fprintf(f,"\nIf the rat moves right and down only, the path of the rat may be\n (S:(%d,%d)|E:(%d,%d)):\n\n",sx+1,sy+1,ex+1,ey+1);

        if(ratMap(arr,sx,sy,ex,ey,solMap))
        {
            for( i=0;i<n;i++)
            {
                for( j=0;j<n;j++)
                {
                    solMap[i][j]=0;
                }
            }
            ratMapProgress(arr,sx,sy,ex,ey,solMap,n);

            for( i=0;i<n;i++)
            {
                for( j=0;j<n;j++)
                {
                    if(solMap[i][j]==1)
                    {
                        if((i==sx && j==sy) || (i==ex && j==ey))
                        {
                            colorr();
                            delay(0.1);
                            printf("  %d",solMap[i][j]);
                            delay(0.1);
                            reset();
                        }
                        else
                        {
                            color();
                            delay(0.1);
                            printf("  %d",solMap[i][j]);
                            delay(0.1);
                            reset();
                        }
                    }
                    else
                    {
                        printf("  %d",solMap[i][j]);
                    }
                    fprintf(f,"  %d",solMap[i][j]);
                }
                printf("\n");
                fprintf(f,"\n");
            }
			printf("\nPath found!!!");
			fprintf(f,"\nPath found!!!");
			printf("\n\nGame data sucessfully stored in Maze.txt!!!");
            printf("\n\n");
            fprintf(f,"\n\n");
        }
        else
        {
            printf("No valid path exist!!!\n\n");
            fprintf(f,"No valid path exist!!!\n\n");
        }
    }

    else
    {
        printf("\nEnter valid choices!!!\n");
        fprintf(f,"\nEnter valid choices!!!\n");
    }

    fclose(f);
    return 0;
}
