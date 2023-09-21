#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from turtlesim.msg import Pose
from geometry_msgs.msg import Twist

class PoseSubcriberNode(Node):
    
    def __init__(self):
        super().__init__("turtle_controller")
        self.cmd_vel_pub = self.create_publisher(
            Twist, "/turtle1/cmd_vel", 10)
        self.pose_subscriber = self.create_subscription(
            Pose, "/turtle1/pose", self.pose_callback, 10) # za kazdym razem gdy przychodzi nowa wiadomosc
        self.get_logger().info("Turtle controller has been started.")

    def pose_callback(self, pose : Pose): 
        cmd = Twist()
        if pose.x > 8.0 or pose.x < 3.0 or pose.y > 8.0 or pose.y < 3.0:
            cmd.linear.x = 1.2
            cmd.angular.z = 0.6
        else:
            cmd.linear.x = 5.0
            cmd.linear.z = 0.0

        self.cmd_vel_pub.publish(cmd)

def main(args=None):
    rclpy.init(args=args)

    node = PoseSubcriberNode()
    rclpy.spin(node)
    
    rclpy.shutdown()