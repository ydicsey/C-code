/*
 * @lc app=leetcode.cn id=85 lang=c
 *
 * [85] 最大矩形
 */

// @lc code=start
// stack in c
int top = -1;
int stack[205];

void push(int x)
{
    top++;
    stack[top] = x;
    printf("%d", top);
}

int pop()
{
    if (top == -1)
    {
        printf("\nUnderflow!!");
        return 0;
    }
    return stack[top--];
}

int peek()
{
    return stack[top];
}

int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize){
    if(matrixColSize == 0 || matrixSize == 0)
    {
        return 0;
    }
    int row = matrixSize;
    int col = matrixColSize[0];

    // 算出柱子(column)最高的高度
    int height[row][col], result = 0;
    // 需特別處理第0行
    for(int j = 0; j < col; j ++)
    {
        height[0][j] = matrix[0][j] == '1' ? 1:0;
    }
    for(int i = 1; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            height[i][j] = matrix[i][j] == '1' ? height[i-1][j]+1 : 0;
        }
    }

    for(int i = 0; i < row; i++)
    {
        result = fmax(result, largestRectangleArea(height, col, i));
    }

    return result;
}

// leetcode 83
int largestRectangleArea(int **height, int colSize, int bottom)
{
    int maxArea = 0;
    top = -1;

    // 為了計算最大面積，stack會是遞增的
    // stack 中存 index 而不是高度
    push(-1);
    int curIdx = 0;

    while(curIdx < colSize)
    {
        // 若不為遞增的話
        while (peek() != -1 && height[bottom][curIdx] <= height[bottom][peek()])
        {
            maxArea = fmax(maxArea, height[bottom][pop()] * (curIdx - peek() -1));
        }
        push(curIdx++);
    }
    // 若全為遞增的話
    while (peek() != -1)
    {
        maxArea = fmax(maxArea, height[bottom][pop()] * (colSize - peek() -1));
    }
    return maxArea;
}
// @lc code=end

