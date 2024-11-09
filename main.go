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
    var totalDuration time.Duration

    for i := 0; i < 10; i++ {
        start := time.Now()

        file, err := os.Open("test.csv")
        if err != nil {
            fmt.Println("Error:", err)
            return
        }

        reader := csv.NewReader(file)
        records, err := reader.ReadAll()
        if err != nil {
            fmt.Println("Error:", err)
            return
        }
        file.Close()

        var result []Record
        for _, record := range records[1:] { // Skip header
            result = append(result, Record{
                Name: record[0],
                Age:  record[1],
                City: record[2],
            })
        }

        elapsed := time.Since(start)
        totalDuration += elapsed
    }

    averageDuration := totalDuration / 10
    fmt.Printf("Average CSV Parse Time: %s\n", averageDuration)
}