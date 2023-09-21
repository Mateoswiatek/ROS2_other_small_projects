#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

from example_interfaces.msg import String  # importing message, we need to add library to depend

class RobotNewsStationNode(Node):
    def __init__(self):
        super().__init__("robot_news_station")

        self.publisher = self.create_publisher(String, "robot_news", 10) # message type, topic_name, queue - keep message before they are processed.

        self.timer = self.create_timer(1.0, self.publish_news)
        self.counter = 0

        self.get_logger().info(f"{self.__class__.__name__} has been started")


    def publish_news(self):
        msg = String()
        msg.data = f"Hello! {self.counter}"  # konkretne pole w message
        self.publisher.publish(msg)  # publikowanie
        self.counter += 1


def main(args=None):
    rclpy.init(args=args)
    node = RobotNewsStationNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()