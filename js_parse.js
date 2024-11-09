const fs = require('fs');
const csv = require('csv-parser');

const results = [];

console.time('CSV Parse Time');

fs.createReadStream('test.csv')
  .pipe(csv())
  .on('data', (data) => results.push(data))
  .on('end', () => {
    console.timeEnd('CSV Parse Time');
  });