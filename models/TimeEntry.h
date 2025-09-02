#ifndef TIMEENTRY_H
#define TIMEENTRY_H
#include <QDateTime>

class TimeEntry {
private:
    int trackId;
    int taskId;
    QDateTime startTime;
    QDateTime endTime;
    int durationMinutes;

public:
    TimeEntry() = default;
    TimeEntry(int trackId, int taskId,
              const QDateTime &start,
              const QDateTime &end,
              int durationMinutes);

    int getTrackId() const;
    void setTrackId(int id);

    int getTaskId() const;
    void setTaskId(int id);

    QDateTime getStartTime() const;
    void setStartTime(const QDateTime &dt);

    QDateTime getEndTime() const;
    void setEndTime(const QDateTime &dt);

    int getDurationMinutes() const;
    void setDurationMinutes(int d);
};

#endif // TIMEENTRY_H
