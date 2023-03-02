#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>

int main()
{
    int n_people;
    int times = 0;

    while(scanf("%d", &n_people) && n_people)
    {
        if(!(times == 0))
        {
            printf("\n");
        }
        times++;
        int lines;
        int *wins = (int*)malloc(n_people * sizeof(int));
        int *lose = (int*)malloc(n_people * sizeof(int));

        scanf("%d", &lines);
        int cnt = (lines * n_people * (n_people-1)) >> 1;
        
        for(int i = 0; i < cnt; i++)
        {
            char gesture_A[10], gesture_B[10];
            int player_A, player_B;

            scanf("%d %s %d %s", &player_A, gesture_A, &player_B, gesture_B);
            // printf("%d %s %d %s\n", player_A, gesture_A, player_B, gesture_B);

            if ( !(gesture_A[0] == gesture_B[0])) 
            {
                if(gesture_A[0] == 'r' && gesture_B[0] == 's' || gesture_A[0] == 's' && gesture_B[0] == 'p' || gesture_A[0] == 'p' && gesture_B[0] == 'r')
                {
                    // Player_A 贏了
                    wins[player_A-1] ++;
                    lose[player_B-1] ++;
                }
                else 
                {
                    // Player_B贏了
                    wins[player_B-1] ++;
                    lose[player_A-1] ++;
                }
            }
        }

        for(int i = 0; i < n_people; i++)
        {
            if(0 == (wins[i] + lose[i]))
            {
                printf("-\n");
            }
            else
            {
                // printf(" %.3f %d %d\n", ((float)wins[i] / (float)(wins[i] + lose[i])), wins[i], lose[i]);
                printf("%.3f\n", ((float)wins[i] / (float)(wins[i] + lose[i])));
            }
        }
    }
}