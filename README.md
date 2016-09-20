# IF3170_LocalSearch

## Spesifikasi CSP
#### Variable : Setiap Mata Kuliah yang diberikan
#### Domain : Ruang, Hari, Jam [akan diassign ke dalam currentRoom, currentDay, dan currentStartTime]
#### Constraint (scope Course):
* `currentStartTime` dan `(currentStartTime+courseDuration)` berada di dalam `courseStartTime` dan `courseEndTime`
* `currentDay ← x` IFF `course.isDayAvail(x)`

#### Constraint (scope Room) :
* `currentStartTime` dan `(currentStartTime+courseDuration)` berada di dalam `roomStartHours` dan `roomEndHours`
* `currentDay ← x` IFF `currentRoom.isDayAvail(x)`
* Course dengan `butuhRuang <> "-"` (butuh ruangan), `currentRoom ← butuhRuang`
* Jika room `this.currentRoom == x`, tidak ada course lain yang `currentRoom` nya juga `x` untuk rentang waktu `this.currentStartTime` hingga `this.currentStartTime + Duration`

