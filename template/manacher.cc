int even_len[kLength];
int odd_len[kLength];
//manacher algorithm
void find_palindrome_substring(char *s, int n) {
  int ptr = -1, length;
  //even length palindrome substring count
  for (int i = 0; i < n - 1; i++) {
    if (ptr == -1 || ptr + even_len[ptr] <= i)
      length = 0;
    else
      length = std::min(ptr + even_len[ptr] - i, even_len[2 * ptr - i]);
    while (i - length >= 0 && i + length < n - 1 && s[i - length] == s[i + length + 1]) ++length;
    even_len[i] = length;
    if (ptr == -1 || i + even_len[i] > ptr + even_len[ptr]) ptr = i;
  }

  //odd length palindrome substring count
  ptr = -1;
  for (int i = 0; i < n; i++) {
    if (ptr == -1 || ptr + odd_len[ptr] < i) 
      length = 0;
    else
      length = std::min(ptr + odd_len[ptr] - i, odd_len[2 * ptr - i]);
    while (i - length > 0 && i + length < n - 1 && s[i - length - 1] == s[i + length + 1]) ++length;
    odd_len[i] = length;
    if (ptr == -1 || i + odd_len[i] > ptr + odd_len[i]) ptr = i;
  }
}
