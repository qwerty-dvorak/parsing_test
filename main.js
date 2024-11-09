const fs = require('fs');
const csv = require('csv-parser');

const results = [];
const times = [];

function parseCSV(callback) {
  const start = process.hrtime();

  fs.createReadStream('test.csv')
    .pipe(csv())
    .on('data', (data) => results.push(data))
    .on('end', () => {
      const end = process.hrtime(start);
      const elapsedTime = end[0] * 1e9 + end[1]; // Convert to nanoseconds
      times.push(elapsedTime);
      callback();
    });
}

function runTimes(n, callback) {
  if (n === 0) {
    callback();
    return;
  }
  parseCSV(() => runTimes(n - 1, callback));
}

runTimes(10, () => {
  const total = times.reduce((acc, time) => acc + time, 0);
  const average = total / times.length;
  console.log(`Average CSV Parse Time: ${(average / 1e6).toFixed(3)} ms`);
});