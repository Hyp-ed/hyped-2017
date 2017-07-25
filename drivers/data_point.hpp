#ifndef DATAPOINT_H_
#define DATAPOINT_H_

template <typename T>
class DataPoint
{
  public:
    double timestamp;
    T value;

    DataPoint() : timestamp(0.0)
    {}
    DataPoint(double timestamp, T value) : timestamp(timestamp), value(value)
    {}

    static DataPoint<T> integrate(const DataPoint<T>& dp0,
        const DataPoint<T>& dp);
};

template <typename T>
DataPoint<T> DataPoint<T>::integrate(const DataPoint<T>& dp0,
    const DataPoint<T>& dp)
{
  return DataPoint(dp.timestamp,
      (dp.timestamp - dp0.timestamp) * (dp.value + dp0.value) / 2.0);
}


#endif //DATAPOINT_H_
