package main

import (
    "encoding/csv"
    "fmt"
    "os"
    "time"
)

type Record struct {
    Name string
    Age  string
    City string
}

func main() {
    start := time.Now()

    file, err := os.Open("test.csv")
    if err != nil {
        fmt.Println("Error:", err)
        return
    }
    defer file.Close()

    reader := csv.NewReader(file)
    records, err := reader.ReadAll()
    if err != nil {
        fmt.Println("Error:", err)
        return
    }

    var result []Record
    for _, record := range records[1:] { // Skip header
        result = append(result, Record{
            Name: record[0],
            Age:  record[1],
            City: record[2],
        })
    }

    elapsed := time.Since(start)
    fmt.Printf("CSV Parse Time: %s\n", elapsed)
}