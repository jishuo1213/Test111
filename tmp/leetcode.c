#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
int addDigits(int num) {

  int sum = 0;
  while (num > 0) {
    sum += num % 10;
    num = num / 10;
  }

  if (sum < 10) {
    return sum;
  }

  return addDigits(sum);
}

long long subArrayRange(int *nums, int start, int end) {
  if (start == end) {
    return 0;
  }
  int max = nums[start], min = nums[start];

  for (int i = start; i < end + 1; i++) {
    if (nums[i] > max) {
      max = nums[i];
    }
    if (nums[i] < min) {
      min = nums[i];
    }
  }
  return max - min;
}

long long subArrayRanges(int *nums, int numsSize) {
  long long result = 0;
  for (int i = 0; i < numsSize; i++) {
    int min = nums[i];
    int max = nums[i];
    for (int j = i + 1; j < numsSize; j++) {
      min = nums[j] < min ? nums[j] : min;
      max = nums[j] > max ? nums[j] : max;
      result += max - min;
      // result += subArrayRange(nums,i,j);
    }
  }
  return result;
}

int findLUSlength(char *a, char *b) {
  int lena = strlen(a);
  int lenb = strlen(b);
  if (lena != lenb) {
    return lena > lenb ? lena : lenb;
  }
  // for (int c = 0; c < lena; c++) {

  for (int i = 0; i < lena; i++) {
    if (a[i] != b[i]) {
      return lena;
    }
  }
  // }
  return -1;
}

int *goodDaysToRobBank(int *security, int securitySize, int time,
                       int *returnSize) {
  int *left = (int *)malloc(sizeof(int) * securitySize); // i点左侧递减的个数
  int *right = (int *)malloc(sizeof(int) * securitySize); // i点右侧递增的个数
  memset(left, 0, securitySize * sizeof(int));
  memset(right, 0, securitySize * sizeof(int));
  for (int i = 1; i < securitySize; i++) {
    if (security[i] <= security[i - 1]) {
      left[i] = left[i - 1] + 1;
    }
    if (security[securitySize - i] >= security[securitySize - i - 1]) {
      right[securitySize - i - 1] = right[securitySize - i] + 1;
    }
  }
  int *result = (int *)malloc(sizeof(int) * securitySize);
  int count = 0;
  for (int i = time; i < securitySize - time; i++) {
    if (right[i] >= time && left[i] >= time) {
      result[count++] = i;
    }
  }
  *returnSize = count;
  free(left);
  free(right);
  return result;
}

double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2,
                              int nums2Size) {
  int *tmpArray = (int *)malloc(sizeof(int) * (nums1Size + nums2Size));
  memset(tmpArray, 0, sizeof(int) * (nums1Size + nums2Size));

  for (int i = 0, j = 0, index = 0; i < nums1Size || j < nums2Size; index++) {
    if (i >= nums1Size) {
      tmpArray[index] = nums2[j];
      j++;
      continue;
    }
    if (j >= nums1Size) {
      tmpArray[index] = nums1[i];
      i++;
      continue;
    }
    if (nums1[i] > nums2[j]) {
      tmpArray[index] = nums2[j];
      j++;
    } else {
      tmpArray[index] = nums1[i];
      i++;
    }
  }
  int mid = (nums1Size + nums2Size) / 2;

  if ((nums1Size + nums2Size) % 2 == 0) {
    return (double)(tmpArray[mid] + tmpArray[mid + 1]) / 2;
  } else {
    return (double)tmpArray[mid];
  }
}

char *longestPalindrome(char *s) {
  int len = strlen(s);
  int left = 0;
  int right = 1;
  int maxLeftIndex = 0;
  int maxRightIndex = 0;
  int maxLength = 1;
  //   printf("left:%d right:%d\n",left,right);
  while (1) {
    if (right >= len) {
      left++;
      right = left + 1;
      //   continue;
      if (left >= len || right >= len) {
        break;
      }
    }
    int isNotTarget = 0;
    for (int l = left, r = right; l <= r; l++, r--) {
      if (s[left] != s[right]) {
        isNotTarget = 1;
        break;
      }
    }
    int length = right - left + 1;
    if (isNotTarget) {
      right += length - 1;
    } else {
      //   printf("111 %d %d %d \n", maxLength, left, right);
      if (length > maxLength) {
        maxLeftIndex = left;
        maxRightIndex = right;
        maxLength = length;
      }

      right++;
    }
  }

  // printf("111 %d %d %d \n", maxLength, maxLeftIndex, maxRightIndex);
  char *ans = (char *)malloc((maxLength + 1) * sizeof(char));
  memset(ans, 0, (maxLength + 1));
  int c = 0;
  for (int i = maxLeftIndex; i <= maxRightIndex; i++) {
    //   printf("111 %d %d %d \n",maxLength,left,right);
    ans[c] = s[i];
    c++;
  }

  return ans;
}

int isMatch(char *s, char *p) {
  int pLen = strlen(p);
  for (int i = 0; i < pLen; i++) {
    if (p[i] == '.') {
    }
  }
}

struct ListNode {
  int val;
  struct ListNode *next;
};

struct ListNode *mergeTwoList(struct ListNode *list1, struct ListNode *list2) {
  struct ListNode *tmp = (struct ListNode *)malloc(sizeof(struct ListNode));
  memset(tmp, 0, sizeof(struct ListNode));
  struct ListNode *ans = tmp;
  while (list1 || list2) {
    int val1, val2;
    val1 = list1 ? list1->val : INT_MAX;
    val2 = list2 ? list2->val : INT_MAX;
    if (val1 > val2) {
      tmp->next = list2;
      list2 = list2->next;
    } else {
      tmp->next = list1;
      list1 = list1->next;
    }
    tmp = tmp->next;
  }
  return ans->next;
}

struct ListNode *mergeKLists(struct ListNode **lists, int listsSize) {
  if (listsSize == 0) {
    return NULL;
  } else if (listsSize == 1) {
    return lists[0];
  } else if (listsSize == 2) {
    return mergeTwoList(lists[0], lists[1]);
  } else {
    int mid = listsSize >> 1;
    return mergeTwoList(mergeKLists(lists, mid),
                        mergeKLists(lists + mid, listsSize - mid));
  }
  // struct ListNode *ans = lists[0];

  // for (int i = 1; i < listsSize; i++) {
  //   ans = mergeTwoList(ans, lists[i]);
  // }
  // return ans;
}

struct ListNode *swapPairs(struct ListNode *head) {
  struct ListNode *tmp = head;
  struct ListNode *prevNode = NULL;
  struct ListNode *lastPrevNode =
      (struct ListNode *)malloc(sizeof(struct ListNode));
  struct ListNode *ans = lastPrevNode;
  lastPrevNode->next = head;
  while (tmp) {
    if (prevNode == NULL) {
      prevNode = tmp;
      tmp = tmp->next;
    } else {
      prevNode->next = tmp->next;
      tmp->next = prevNode;
      if (lastPrevNode) {
        lastPrevNode->next = tmp;
      }
      lastPrevNode = prevNode;
      tmp = prevNode->next;
      prevNode = NULL;
    }
  }
  return ans->next;
}

struct ListNode *reverseList(struct ListNode *head, int n) {
  struct ListNode *tail = (struct ListNode *)malloc(sizeof(struct ListNode));
  memset(tail, 0, sizeof(struct ListNode));
  // dummyHead->next = head;

  // struct ListNode *tail = dummyHead;
  int c = 0;
  struct ListNode **skt =
      (struct ListNode **)malloc(n * sizeof(struct ListNode *));
  memset(skt, 0, n * sizeof(struct ListNode *));
  // printf("head:val:%d\n", head->val);
  int top = 0;
  struct ListNode *tmp = head;
  while (tmp && c < n) {
    skt[top++] = tmp;
    c++;
    if (tmp->next == NULL && c < n) {
      // *newTail = tmp;
      return head;
    }
    tmp = tmp->next;
  }
  struct ListNode *nextNode = skt[top - 1]->next;
  struct ListNode *ans = skt[top - 1];
  for (int i = c - 1; i >= 0; i--) {
    tail->next = skt[--top];
    tail = tail->next;
    // printf("%d\n", tail->val);
  }
  tail->next = nextNode;
  return ans;
}

struct ListNode *reverseKGroup(struct ListNode *head, int k) {
  if (k == 1) {
    return head;
  }
  struct ListNode *tail = head;
  struct ListNode *prevNode =
      (struct ListNode *)malloc(sizeof(struct ListNode));
  memset(prevNode, 0, sizeof(struct ListNode));
  prevNode->next = head;
  struct ListNode *ans = prevNode;

  int index = 0;
  while (tail) {
    if (index % k == 0) {
      struct ListNode *newHead = reverseList(tail, k);
      prevNode->next = newHead;
      tail = newHead;
    } else if (index % k == k - 1) {
      prevNode = tail;
    }
    index++;
    tail = tail->next;
  }
  return ans->next;
}

int removeDuplicates(int *nums, int numsSize) {
  int fast = 1;
  int slow = 0;
  for (int fast = 1; fast < numsSize; fast++) {
    if (nums[fast] != nums[slow]) {
      nums[slow + 1] = nums[fast];
      slow++;
    }
  }
  return slow + 1;
}

int removeElement(int *nums, int numsSize, int val) {
  int fast = 0;
  int slow = 0;
  for (int fast = 0; fast < numsSize; fast++) {
    if (nums[fast] != val) {
      nums[slow] = nums[fast];
      slow++;
    }
  }
  return slow;
}

int compInt(const void *left, const void *right) {
  int *l = (int *)left;
  int *r = (int *)right;
  return *l - *r;
}

void dfs(int pos, int currentOrVal, int *nums, int numSize, int *maxOrVal,
         int *cnt) {
  if (pos == numSize) {
    if (currentOrVal > *maxOrVal) {
      *maxOrVal = currentOrVal;
      *cnt = 1;
    } else if (currentOrVal == *maxOrVal) {
      (*cnt)++;
    }
  }
  dfs(pos + 1, currentOrVal | nums[pos], nums, numSize, maxOrVal, cnt);
  dfs(pos + 1, currentOrVal, nums, numSize, maxOrVal, cnt);
}

int countMaxOrSubsets(int *nums, int numsSize) {
  int maxOrVal = 0;
  int cnt = 0;
  dfs(0, 0, nums, numsSize, &maxOrVal, &cnt);
  return cnt;
}

int strStr(char *haystack, char *needle) {
  int hLen = strlen(haystack);
  int nLen = strlen(needle);
  if (nLen == 0) {
    return 0;
  }
  if (hLen < nLen) {
    return -1;
  }
  int hIndex = -1;
  for (int i = 0; i <= hLen - nLen; i++) {
    hIndex = i;
    int tIndex = hIndex;
    int isFound = 1;
    for (int j = 0; j < nLen; j++) {
      if (needle[j] != haystack[tIndex]) {
        isFound = 0;
        break;
      }
      tIndex++;
    }
    if (isFound) {
      break;
    }
    hIndex = -1;
  }
  return hIndex;
}

void nextPermutation(int *nums, int numsSize) {
  int ans[numsSize];
  // memcpy(ans, nums, numsSize * sizeof(int));
  // qsort(nums, numsSize, sizeof(int), compInt)
  if (numsSize == 1) {
    return;
  }

  int index = 0;
  int min = INT_MAX;
  int minIndex = 0;
  for (int i = numsSize - 1; i >= 0; i--) {
    if (i - 1 >= 0) {
      if (nums[i] > nums[i - 1]) {
        int changeIndex = i;
        // if (nums[numsSize - 1] > nums[i - 1]) {
        //   changeIndex = numsSize - 1;
        // }
        // int tmp = nums[changeIndex];
        // nums[changeIndex] = nums[i - 1];
        // nums[i - 1] = tmp;

        // index = i;
        // if (nums[i + 1] >= nums[i - 1]) {
        //   changeIndex = i;
        // }
        for (int j = i + 1; j < numsSize; j++) {
          if (nums[j] >= nums[i - 1]) {
            changeIndex = j;
          } else {
            break;
          }
        }
        int tmp = nums[changeIndex];
        nums[changeIndex] = nums[i - 1];
        nums[i - 1] = tmp;
        break;
      }
    }
  }
  // printf("index:%d %d %d %d",index,nums[0],nums[1],nums[2]);
  qsort(nums + index, numsSize - index, sizeof(int), compInt);
  return;
}

char *simplifyPath(char *path) {
  int pLen = strlen(path);
  char *skt[1000];
  int top = 0;
  // for (int i = 0; i < pLen;) {
  int index = 0;
  while (index < pLen) {
    int start = -1;
    int end = -1;
    int tmp = index;
    while (path[tmp] == '/' && tmp < pLen) {
      tmp++;
    }
    start = tmp;
    while (path[tmp] != '/' && tmp < pLen) {
      tmp++;
    }
    end = tmp;

    if (start < pLen) {
      char *name = (char *)malloc(end - start + 1);
      memset(name, 0, end - start + 1);
      strncpy(name, path + start, end - start);
      printf("name:%s\n", name);
      if (!strcmp(name, ".")) {
        continue;
      } else if (!strcmp(name, "..")) {
        top--;
      } else {
        skt[top] = name;
        top++;
      }
    }
    index = end;
  }
  char *ans = (char *)malloc(3000);
  memset(ans, 0, 3000);
  int ansIndex = 0;
  if (top <= 0) {
    ans[ansIndex] = '/';
  }
  for (int i = 0; i < top; i++) {
    ans[ansIndex] = '/';
    strncpy(ans + ansIndex + 1, skt[i], strlen(skt[i]));
    ansIndex = ansIndex + 1 + strlen(skt[i]);
  }
  return ans;
}

int minInt(int a, int b) { return a < b ? a : b; }

int minDistance(char *word1, char *word2) {
  int word1Len = strlen(word1);
  int word2Len = strlen(word2);
  int dp[word1Len + 1][word2Len + 1];
  dp[0][0] = 0;
  for (int i = 1; i <= word2Len; i++) {
    dp[0][i] = i;
  }
  for (int i = 1; i <= word1Len; i++) {
    dp[i][0] = i;
  }
  for (int i = 1; i <= word1Len; i++) {
    for (int j = 1; j <= word2Len; j++) {
      if (dp[i - 1] == dp[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        int dis1 = dp[i - 1][j] + 1;     //删除
        int dis2 = dp[i][j - 1] + 1;     //新增
        int dis3 = dp[i - 1][j - 1] + 1; //替换
        dp[i][j] = minInt(minInt(dis1, dis2), dis3);
      }
    }
  }
  return dp[word1Len][word2Len];
}

int compIntDesc(const void *left, const void *right) {
  int *l = (int *)left;
  int *r = (int *)right;
  return *l - *r;
}

int compIntAsc(const void *left, const void *right) {
  int *l = (int *)left;
  int *r = (int *)right;
  return *l - *r;
}

int search(int *nums, int numsSize, int target) {
  int left = 0;
  int right = numsSize - 1;
  while (left < right) {
    int mid = left + (right - left) / 2;

    if (nums[left] < nums[mid] && nums[mid] < nums[right]) {
      int *res = (int *)bsearch(&target, nums + left, right - left + 1,
                                sizeof(int), compIntAsc);
      if (res) {
        return res - nums;
      }
      return -1;
    }
    printf("left:%d right:%d mid:%d\n", left, right, mid);
    if (nums[mid] > nums[right]) {
      int *res = (int *)bsearch(&target, nums + left, mid - left + 1,
                                sizeof(int), compIntAsc);
      if (res) {
        return res - nums;
      }
      left = mid + 1;
    } else {
      int *res = (int *)bsearch(&target, nums + mid, right - mid + 1,
                                sizeof(int), compIntAsc);
      if (res) {
        return res - nums;
      }
      right = mid - 1;
    }
  }
  return -1;
}

int *searchRange(int *nums, int numsSize, int target, int *returnSize) {
  int *res = (int *)bsearch(&target, nums, numsSize, sizeof(int), compIntAsc);
  *returnSize = 2;
  int *ans = (int *)malloc(sizeof(int) * 2);
  if (res) {
    // for()
    int index = res - nums;
    for (int i = index; i >= 0; i--) {
      if (nums[i] == target) {
        ans[0] = i;
        continue;
      }
      break;
    }
    for (int i = index; i <= numsSize - 1; i++) {
      if (nums[i] == target) {
        ans[1] = i;
        continue;
      }
      break;
    }
  }
  return ans;
}

int searchInsert(int *nums, int numsSize, int target) {
  int left = 0;
  int right = numsSize - 1;
  int mid;
  while (left <= right) {
    mid = left + (right - left) / 2;
    if (nums[mid] == target) {
      return mid;
    }
    if (nums[mid] > target) {
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
  return mid;
}

bool isValidSudoku(char **board, int boardSize, int *boardColSize) {
  int colResult[9] = {0};
  int lineResult[9] = {0};
  int squreResult[9] = {0};
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (board[i][j] == '.') {
        continue;
      }
      printf("i:%d j:%d c:%c", i, j, board[i][j]);
      if (!colResult[i]) {
        int nums[9] = {0};
        for (int k = 0; k < 9; k++) {
          if (board[i][k] == '.') {
            continue;
          }
          int num = board[i][k] - '0';
          if (nums[num]) {
            return false;
          }
          nums[num] = 1;
        }
        colResult[i] = 1;
      }

      if (!colResult[j]) {
        int nums[9] = {0};
        for (int k = 0; k < 9; k++) {
          if (board[k][j] == '.') {
            continue;
          }
          int num = board[k][j] - '0';
          if (nums[num]) {
            return false;
          }
          nums[num] = 1;
        }
        colResult[i] = 1;
      }
      int squreIndex = 0;
      if (j / 3 == 0) {
        squreIndex = i / 3;
      }
      if (j / 3 == 1) {
        squreIndex = i / 3 + 3;
      }
      if (j / 3 == 2) {
        squreIndex = i / 3 + 6;
      }
      if (!squreResult[squreIndex]) {
        int nums[9] = {0};
        for (int l = 0; l < 3; l++) {
          for (int c = 0; c < 3; c++) {
            if (board[i + l][j + c] == '.') {
              continue;
            }
            int num = board[i + l][j + c] - '0';
            if (nums[num]) {
              return false;
            }
            nums[num] = 1;
          }
        }
        squreResult[squreIndex] = 1;
      }
    }
  }
  return true;
}

int maxConsecutive(char *answerKey, int k, char c) {
  int ansLen = strlen(answerKey);
  int start = 0;
  int end = 0;
  int sum = 0;
  int maxCnt = 0;
  for (int i = 0; i < ansLen; i++) {
    if (answerKey[i] != c) {
      sum++;
    }
    while (sum > k) {
      if (answerKey[start] != c) {
        sum--;
      }
      start++;
    }
    if ((end - start + 1) > maxCnt) {
      maxCnt = end - start + 1;
    }
    end = i;
  }
  return maxCnt;
}

int longestOnes(int *nums, int numsSize, int k) {
  int start = 0;
  int end = 0;
  int step = 0;
  int maxCnt = 0;
  for (int i = 0; i < numsSize; i++) {
    if (nums[i] != 1) {
      step++;
    }
    while (step > k) {
      if (nums[start] != 1) {
        step--;
      }
      start++;
    }
    end = i;
    if (end - start + 1 > maxCnt) {
      maxCnt = end - start + 1;
    }
  }
  return maxCnt;
}

int lengthOfLongestSubstring(char *s) {
  int sLen = strlen(s);
  int start = 0;
  // int end = 0;

  // char charList[27];
  int maxLength = 0;
  for (int end = 0; end < sLen; end++) {
    int isSame = 0;
    for (int j = start; j < end; j++) {
      if (s[end] == s[j]) {
        isSame = 1;
        start = j + 1;
        break;
      }
    }
    if (end - start + 1 > maxLength) {
      maxLength = end - start + 1;
    }
  }
  return maxLength;
}

int maxConsecutiveAnswers(char *answerKey, int k) {
  int max1 = maxConsecutive(answerKey, k, 'F');
  int max2 = maxConsecutive(answerKey, k, 'T');
  return max1 > max2 ? max1 : max2;
}
