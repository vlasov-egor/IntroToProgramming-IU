package com.company;
import java.util.Scanner;

public class Main {
    public static void main (String[] args) {
        // Scanner
        Scanner input = new Scanner(System.in);        
        int n = input.nextInt();
        int[] a = new int[n];

        for (int i = 0; i < n; ++i) {
            a[i] = i;
        }

        for (int i = 0; i < n; ++i) {
            System.out.println(a[i]);
        }
    }
}