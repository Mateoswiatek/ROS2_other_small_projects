#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from turtlesim.msg import Pose

class PoseSubcriberNode(Node):
    
    def __init__(self):
        super().__init__("pose_subcriber")
        self.pose_subcriber = self.create_subscription(
            Pose, "/turtle1/pose", self.pose_callback, 10)  # datatype,name, callback, buffor

    def pose_callback(self, msg: Pose):  # one parametr - message from Topic, msg jest typu Pose, autocompletion
        self.get_logger().info(f"x={str(msg.x)}, y={str(msg.y)}") # msg is objects


def main(args=None):
    rclpy.init(args=args)
    
    node = PoseSubcriberNode()
    rclpy.spin(node)

    rclpy.shutdown()