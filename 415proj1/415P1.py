#Author: Timothy Gallagher, Jeff Olson
#Date: 2/8/19
#Professor: Dr. Gill
#Class: CS 415
#Assignment: Project 1
#Purpose:

import numpy as np
from collections import Counter
import matplotlib
#matplotlib.use('Agg')
import matplotlib.pyplot as plt
import random
import time
#import pandas as pd


#TODO:
    # Compute Euclids alogorithm and Consecutive integer algorithm for GCD
def main():
    print("Project 1 : Empirical Analysis of Algorithms")
    run()
    # while (i <= a):
    #     c, temp  = euclid_gcd_recursive(a, i, 0)
    #     sum_euclids += temp
    #     x_euclid.append(temp)
    #     y_euclid.append(i)
    #     #gcd_euclid_list.append(c)
    #     #d = middle_school_gcd_iterative(a, i)
    #     #gcd_middle_list.append(d)
    #     e, temp1 = consecutive_int_check_gcd(a, i)
    #     sum_iterative += temp1
    #     x_iterative.append(temp1)
    #     y_iterative.append(i)
    #     i += 1
    # print("The average case time for the recursive Euclids algorithm on input n = ", a, " is: ", (sum_euclids/a))
    # print("The average case time for the Iterative version on input n = ", a, " is: ", (sum_iterative / a))
    # fib_seq = []
    # sum_euclids_fib = int(0)
    # temp = 0
    # i = int(1)
    # while (i <= a):
    #     c, temp = euclid_gcd_recursive(fib_nums(i), fib_nums(i+1), 0)
    #     sum_euclids_fib += temp
    #     i+=1
    # print("The worst case time for the recursive Euclids algorithm using the fib sequence on input k = ", a, " is: ", (sum_euclids_fib / a))


    return 0

def run():
    i = int(0)
    while i != 3:
        i = int(input("Would you like to enter (1) User Testing Mode, (2) Scatter plot mode, or (3) Quit: "))
        sum_euclids = float(0)
        sum_iterative = float(0)
        x_euclid = []
        y_euclid = []
        x_iterative = []
        y_iterative = []
        x_ms = []
        y_ms = []
        if i == 1:
            #Tell user about task 1
            i = 1
            n = int(input("Task 1, Please enter your n: "))
            while (i <= n):
                count = int(0)
                count1 = int(0)
                num_gcd_euclids, count = euclid_gcd_recursive(n, i, 0)
                sum_euclids += count
                num_gcd_consecutive, count1 = consecutive_int_check_gcd(n, i)
                sum_iterative += count1
                i+=1
            print("MDavg(", n, ") = ", (sum_euclids / n))
            print("Davg(", n, ") = ", (sum_iterative / n))
            #Tell user about task 2
            k = int(input("Task 2, Please enter your k: "))
            sum_euclids_fib = int(0)
            temp2 = int(0)
            i = int(1)
            while (i <= k):
                num_gcd_euclid_fib, temp2 = euclid_gcd_recursive(fib_nums(i), fib_nums(i + 1), 0)
                sum_euclids_fib += temp2
                i += 1
            print("GCD(m, n) where m = F(k+1) and n = F(k) are consecutive elements of the Fibonacci sequence = ", (sum_euclids_fib / k))
            #Tell user about task 3
            answer = int(0)
            print("Task 3")
            m = int(input("Please enter your m: "))
            n = int(input("Please enter your n: "))
            answer, temp3 = euclid_gcd_recursive(n,m,0)
            print("GCD(", m, ", ", n,") = ", answer)
        if i == 2:
            #Task #1
            print("Task 1: Printing scatter plot of MDAvg(n) and DAvg(n)...")
            sum_e = float(0)
            sum_c = float(0)
            xMD_lst = []
            xD_lst = []
            y_lst = []
            y2_lst = []
            start_time_t1 = float(0)
            end_time_t1 = float(0)
            time_t1_lst = []
            n_lst = []
            it = int(1)

            while (it < 1000):
                count = int(0)
                count2 = int(0)
                tempr = random.randint(1, 1001)
                start = time.clock()
                ngcd_eu, count = euclid_gcd_recursive(tempr, it, 0)
                end_time_t1 = (time.clock() - start_time_t1)
                time_t1_lst.append(end_time_t1)
                sum_e += count
                ngcd_con, count2 = consecutive_int_check_gcd(tempr, it)

                sum_c += count2
                mdavg = sum_e/tempr
                davg = sum_c/tempr

                xMD_lst.append(mdavg)
                xD_lst.append(davg)
                y_lst.append(it)
                y2_lst.append(it)
                n_lst.append(tempr)
                it+=1

            x = np.concatenate((xMD_lst, xD_lst))
            y = np.concatenate((y_lst, y2_lst))
            color_arr = ['r'] * len(xMD_lst) + ['g'] * len(xD_lst)

            #Compute
            sum_time_t1 = float(0)
            for elem in time_t1_lst:
                sum_time_t1 += elem
            time_avg_t1 = sum_time_t1/len(time_t1_lst)
            print("time average task 1: ", time_avg_t1)


            sum_MD = float(0)
            for elem in xMD_lst:
                sum_MD += elem
            avg_md = sum_MD/len(xMD_lst)
            print("Average of MD: ", avg_md)

            sum_D = float(0)
            for elem in xD_lst:
                sum_D += elem
            avg_d = sum_D/len(xD_lst)
            print("Average of D: ", avg_d)



            #Plot
            plt.axis([0,len(y_lst), 0, len(x)])
            fig_size = plt.rcParams["figure.figsize"]
            fig_size[0] = 10
            fig_size[1] = 10
            plt.rcParams["figure.figsize"] = fig_size
            plt.scatter(y, x, s=7, c=color_arr, alpha=0.5)
            plt.title("Task1Plot")
            plt.xlabel('1000 different Ns')
            plt.ylabel('red:MDAvg   green:DAvg')
            plt.show()


            #Task 2
            print("Task 2: Printing scatterplot.. ")
            num_MD_div = int(0)
            start_time = float(0)
            end_time = float(0)
            sum_MD_t2 = float(0)
            xMD_lst_t2 = []     #array for num modulo divisions for each iteration
            y_lst_t2 = []
            time_lst = []
            c = int(1)
            k = int(1)
            while (c < 900):
                k = random.randint(1,100)
                m = fib_nums(c+1)
                n = fib_nums(c)
                #print("k: ", k, "m: ", m, "n: ", n)
                start = time.clock()
                temp, num_MD_div = euclid_gcd_recursive(m,n,0)
                end_time = (time.clock() - start_time)
                time_lst.append(end_time)
                y_lst_t2.append(c)
                xMD_lst_t2.append(num_MD_div)
                c+=1

            time_sum = float(0)
            for elem in time_lst:
                time_sum += elem
            time_avg = time_sum/len(time_lst)
            print("Average time taken", time_avg)

            #color_arr = ['r'] * len(xMD_lst_t2) + ['g'] * len(y)
            #plt.axis([0,len(y_lst_t2), 0, len(xMD_lst_t2)])
            plt.rcParams["figure.figsize"] = fig_size
            plt.scatter(y_lst_t2, xMD_lst_t2, s=10, c="red", alpha=0.5)
            plt.title("Task2Plot")
            plt.xlabel('K')
            plt.ylabel('Modulo Average')
            plt.show()

            print("ScatterPlot for time")


            #Task 3
            ms_sum = int(0)
            ms_count = int(0)
            temp3 = int(0)
            ms_lst = []
            msy_lst = []
            msc_lst = []
            c = int(1)
            while(c < 10000):
                ms_count = 0
                m = random.randint(1,c)
                n = random.randint(1,m)
                temp3, ms_count = middle_school_gcd_iterative (m,n, ms_count)
                msy_lst.append(temp3)
                msc_lst.append(ms_count)

                c+=1

            for elem in msc_lst:
                print("c: ", elem)
            for elem in msy_lst:
                print("y: ", elem)
            #plt.rcParams["figure.figsize"] = fig_size
            plt.scatter(msc_lst, msy_lst, s=10, c="red", alpha=0.5)
            plt.title("Task3Plot")
            plt.xlabel('SizeofArray')
            plt.ylabel('IC')
            plt.show()



    #Euclids
def euclid_gcd_recursive(n,m, i_r_count):
    if int(m) > int(n):
        return euclid_gcd_recursive(m,n, i_r_count)
    i_r_count+=1
    mod = int(n) % int(m)
    if mod == 0:
        return m, i_r_count

    return euclid_gcd_recursive(m, mod, i_r_count)

def prime_factors(x, icount):
    factors = []
    n = int(x)
    i = 2
    while n > 1:
        if n % int(i) == 0:
            factors.append(i)
            n /= i
        else:
            i += 1
        icount+=1
    return factors, icount

def middle_school_gcd_iterative(n,m, i_i_count):
    i_i_count = 0
    factors_n, i_i_count = prime_factors(n, i_i_count)
    factors_m, i_i_count = prime_factors(m, i_i_count)
    a = len(factors_n)
    b = len(factors_m)
    #both_factors = factors_m & factors_n
    #i_i_count-=1
    if a > b:
        return a, i_i_count
    else:
        return b, i_i_count

def consecutive_int_check_gcd(n,m):
    i_cic_count = int(0)
    t = int(min(m, n)) #needs to get checked in the function call
    while t != 0:
        i_cic_count +=1
        mod = int(m) % t
        if mod == 0:
            mod2 = int(n) % t
            if mod2 == 0:
                i_cic_count +=1
                return t, i_cic_count
        t -= 1

def fib_nums(n):
    a, b = 0, 1
    for i in range (0, n):
        a, b = b, a+b
    return a


def SieveOfEratosthenes(n):
    # Create a boolean array "prime[0..n]" and initialize
    #  all entries it as true. A value in prime[i] will
    # finally be false if i is Not a prime, else true.
    nums = []
    prime = [True for i in range(n + 1)]
    p = 2
    while (p * p <= n):

        # If prime[p] is not changed, then it is a prime
        if (prime[p] == True):

            # Update all multiples of p
            for i in range(p * 2, n + 1, p):
                prime[i] = False
        p += 1
    for p in range(2, n):
        if prime[p]:
            nums.append(p)
    return nums

def ms_procedure_gcd(n,m):
    prime_nums_less_than_k = []
    prime_nums_less_than_k =  SieveOfEratosthenes(n)
    prime_factors_val, temp = prime_factors(n,0)


main()
