{
 "metadata": {
  "name": "",
  "signature": "sha256:d8057691121ae643629943aa53df4582b663c3eee0d0645691dcc7d485204574"
 },
 "nbformat": 3,
 "nbformat_minor": 0,
 "worksheets": [
  {
   "cells": [
    {
     "cell_type": "code",
     "collapsed": false,
     "input": [
      "def is_binary_palindrome(x):\n",
      "    b = bin(x)[2:]    \n",
      "    l = len(b)//2\n",
      "    return b[:l] == b[::-1][:l]\n",
      "\n",
      "def reverse_number(x,base):\n",
      "    r = 0\n",
      "    while x:\n",
      "        r = r*base + x%base\n",
      "        x //= base\n",
      "    return r\n",
      "\n",
      "def range_with_digits(n):\n",
      "    begin = 0\n",
      "    end = 0\n",
      "    while n > 0:\n",
      "        begin = begin*10 if begin else 1\n",
      "        end = 10*end + 9\n",
      "        n -= 1\n",
      "    return begin,end"
     ],
     "language": "python",
     "metadata": {},
     "outputs": [],
     "prompt_number": 31
    },
    {
     "cell_type": "code",
     "collapsed": false,
     "input": [
      "s = 0\n",
      "\n",
      "for l in range(1,6+1):\n",
      "    begin,end = range_with_digits(l//2)\n",
      "    for m in range(10 if l%2==1 else 1):\n",
      "        for k in range(begin,end+1):\n",
      "            n = reverse_number(k,10) + m*10**(l//2) + k*10**(l//2 + l%2)\n",
      "            if is_binary_palindrome(n):\n",
      "                s += n\n",
      "                print n\n",
      "\n",
      "print 'S =',s"
     ],
     "language": "python",
     "metadata": {},
     "outputs": [
      {
       "output_type": "stream",
       "stream": "stdout",
       "text": [
        "0\n",
        "1\n",
        "3\n",
        "5\n",
        "7\n",
        "9\n",
        "33\n",
        "99\n",
        "313\n",
        "717\n",
        "585\n",
        "7447\n",
        "9009\n",
        "32223\n",
        "53235\n",
        "15351\n",
        "73737\n",
        "53835\n",
        "39993\n",
        "585585\n",
        "S = 872187\n"
       ]
      }
     ],
     "prompt_number": 32
    },
    {
     "cell_type": "code",
     "collapsed": false,
     "input": [],
     "language": "python",
     "metadata": {},
     "outputs": []
    }
   ],
   "metadata": {}
  }
 ]
}