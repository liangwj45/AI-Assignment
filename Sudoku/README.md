# 数独的四种解法

- ES（暴力搜索）

- BS（回溯搜索）

- FC（前向检查）

- MRV（最小剩余值优先选择）

## 运行

```bash
# 编译
make
# 运行
./main puzzle/case1
./main puzzle/case2
./main puzzle/case3
./main puzzle/case4
./main puzzle/case5
./main puzzle/easy
./main puzzle/medium
./main puzzle/hard
./main puzzle/expert
./main puzzle/hardest
```

## 测试结果

- **case1**：

| algorithm                          | time(ms)  | iteration    |
| ---------------------------------- | --------- | ------------ |
| Exhaustive Search                  | \>2886.19 | \>50,000,000 |
| Backtracking Search                | 0.0247    | 594          |
| Forward Checking                   | 0.0194    | 9            |
| Minimum Remaining Values (with FC) | 0.0219    | 1            |

- **case2**：

| algorithm                          | time(ms)  | iteration    |
| ---------------------------------- | --------- | ------------ |
| Exhaustive Search                  | \>3812.81 | \>50,000,000 |
| Backtracking Search                | 0.2378    | 7098         |
| Forward Checking                   | 0.0511    | 72           |
| Minimum Remaining Values (with FC) | 0.0711    | 3            |

- **case3**：

| algorithm                          | time(ms)  | iteration    |
| ---------------------------------- | --------- | ------------ |
| Exhaustive Search                  | \>2779.77 | \>50,000,000 |
| Backtracking Search                | 0.43      | 12722        |
| Forward Checking                   | 0.1049    | 117          |
| Minimum Remaining Values (with FC) | 0.1046    | 11           |

- **case4**：

| algorithm                          | time(ms)  | iteration    |
| ---------------------------------- | --------- | ------------ |
| Exhaustive Search                  | \>3545.72 | \>50,000,000 |
| Backtracking Search                | 0.1319    | 4080         |
| Forward Checking                   | 0.1326    | 85           |
| Minimum Remaining Values (with FC) | 0.0927    | 5            |

- **case5**：

| algorithm                          | time(ms)  | iteration    |
| ---------------------------------- | --------- | ------------ |
| Exhaustive Search                  | \>3337.85 | \>50,000,000 |
| Backtracking Search                | 0.0925    | 2069         |
| Forward Checking                   | 0.0446    | 36           |
| Minimum Remaining Values (with FC) | 0.0364    | 1            |

- **easy**：

| algorithm                          | time(ms)  | iteration    |
| ---------------------------------- | --------- | ------------ |
| Exhaustive Search                  | \>3746.85 | \>50,000,000 |
| Backtracking Search                | 0.034     | 683          |
| Forward Checking                   | 0.0123    | 7            |
| Minimum Remaining Values (with FC) | 0.0226    | 1            |

- **medium**：

| algorithm                          | time(ms)  | iteration    |
| ---------------------------------- | --------- | ------------ |
| Exhaustive Search                  | \>2996.52 | \>50,000,000 |
| Backtracking Search                | 2.6649    | 90825        |
| Forward Checking                   | 0.5773    | 838          |
| Minimum Remaining Values (with FC) | 0.0293    | 3            |

- **hard**：

| algorithm                          | time(ms)  | iteration    |
| ---------------------------------- | --------- | ------------ |
| Exhaustive Search                  | \>2751.14 | \>50,000,000 |
| Backtracking Search                | 8.1749    | 245886       |
| Forward Checking                   | 1.4186    | 3302         |
| Minimum Remaining Values (with FC) | 0.0855    | 8            |

- **expert**：

| algorithm                          | time(ms)  | iteration    |
| ---------------------------------- | --------- | ------------ |
| Exhaustive Search                  | \>3119.31 | \>50,000,000 |
| Backtracking Search                | 122.378   | 3745806      |
| Forward Checking                   | 13.7755   | 30774        |
| Minimum Remaining Values (with FC) | 0.2242    | 41           |

- **hardest**：

| algorithm                          | time(ms) | iteration    |
| ---------------------------------- | -------- | ------------ |
| Exhaustive Search                  | \>2828.2 | \>50,000,000 |
| Backtracking Search                | 17457    | 553402282    |
| Forward Checking                   | 3297.29  | 7458113      |
| Minimum Remaining Values (with FC) | 18.8967  | 6046         |
