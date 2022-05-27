import os
from typing import Optional
import sys
import pandas as pd
import requests

def read_df(file_path: str) -> pd.DataFrame:
    """
    读取csv文件
    @param file_path: 文件路径
    @return: 数据框
    """
    file_path = os.path.join(os.path.dirname(__file__), file_path)
    return pd.read_csv(file_path)

class BaiduMap:
    """
    使用该类处理所有有关百度地图API的操作
    """
    def __init__(self):
        self.directionlite_url = 'http://api.map.baidu.com/directionlite/v1/driving'
        self.direction_url = 'http://api.map.baidu.com/direction/v2/driving'
        self.session = requests.Session()

    def login(self, ak: str) -> None:
        """
        使用百度地图API需要提供AK
        @param ak: 从百度地图API的控制台处获得的AK
        """
        self.ak = ak

    def read_lng_lat(self, file_path: str) -> None:
        """
        读取城市经纬度
        @param file_path: 经纬度数据存储路径
        """
        lng_lat_df = read_df(file_path)
        self.lng_lat = {}
        for index in range(len(lng_lat_df)):
            self.lng_lat[lng_lat_df.at[index, 'city']] = (round(lng_lat_df.at[index, 'longitude'], 6), round(lng_lat_df.at[index, 'latitude'], 6))

    def get_lng_lat(self, city_name: str) -> tuple:
        """
        获取城市经纬度
        @param city_name: 城市名字
        @return: 城市的经纬度
        """
        return self.lng_lat[city_name]

    def fetch_route(self, origin: list, destination: list, method: str = 'directionlite') -> dict:
        """
        使用百度地图API获取所需要的信息(里程数,驾车时间,过路费)
        @param origin: 起点的经纬度，经度在前，纬度在后
        @param destination: 终点的经纬度，经度在前，纬度在后
        @param method: 使用轻量路线规划或路线规划API,取值为directionlite或direction
        @return: 返回想要写入数据框中的信息
        """
        if method == 'directionlite':
            url = self.directionlite_url
        elif method == 'direction':
            url = self.direction_url
        params = {
            'origin': f'{origin[1]},{origin[0]}',
            'destination': f'{destination[1]},{destination[0]}',
            'ak': self.ak,
        }
        resp = self.session.get(url = url, params = params).json()
        if resp['status'] == 0:
            routes = resp['result']['routes'][0]
            return {
                'distance': routes['distance'] / 1000,
                'duration': routes['duration'],
                'toll': routes['toll'],
            }
        else:
            print(params)
            raise Exception('调用出错！')

if __name__ == "__main__":
    import time
    map = BaiduMap()
    map.login('Your Baidu Map API AK')
    map.read_lng_lat('cities_lng_lat.csv')
    result_df = read_df('distance.csv')
    print('使用百度地图API读取数据...')
    for index in range(len(result_df)):
        if result_df.at[index, 'baidu_map_distance'] == 0.0:
            origin_city = result_df.at[index, 'origin']
            destination_city = result_df.at[index, 'destination']
            origin_position = map.get_lng_lat(origin_city)
            destination_position = map.get_lng_lat(destination_city)
            try:
                resp = map.fetch_route(origin_position, destination_position, method='direction')
            except:
                print('运行出错了，速速存盘保平安！')
                result_df.to_csv(os.path.join(os.path.dirname(__file__), 'distance.csv'), index=False)
                sys.exit()
            result_df.at[index, 'baidu_map_distance'] = resp['distance']
            result_df.at[index, 'duration'] = resp['duration']
            result_df.at[index, 'toll'] = resp['toll']
            if index % 20 == 19:
                print(f'处理到第 {index + 1} 条数据，准备存盘...')
                result_df.to_csv(os.path.join(os.path.dirname(__file__), 'distance.csv'), index=False)