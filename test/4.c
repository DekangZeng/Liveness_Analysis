void test() {

  int a, b, c, d, e;
  a = b = 5;
  c = 0;
  d = e = 4;

  for(int i = 0; i < 100; i++) 
  {
      c = a - b;
      while (i + e < 20) {
          i = a + i;
      }
      b = c * a;
  }
}

