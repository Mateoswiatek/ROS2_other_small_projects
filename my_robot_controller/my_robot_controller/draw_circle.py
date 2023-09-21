#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist

class DrawCircleNode(Node):
    def __init__(self):
        super().__init__("draw_circle")
        self.cmd_vel_pub = self.create_publisher(Twist, "/turtle1/cmd_vel", 10)  # we create a publisher message_type, topic_name, queue buffor size
        self.timer = self.create_timer(0.22, self.send_velocity_command)  # callback is send_vel...
        self.counter = 1.0
        self.get_logger().info("Draw circle node has been started")
        

    def send_velocity_command(self):
        msg = Twist()  # create message
        msg.linear.x = 3.0 # filled the data
        msg.angular.z = self.counter # filled the data # we musn't fill all the fields
        self.cmd_vel_pub.publish(msg)  # use publis metod ofthe publisher to sen message
        self.counter *= 1.15
        if self.counter >= 15:
            self.counter = 1.0


def main(args=None):
    rclpy.init(args=args)
    node = DrawCircleNode()
    rclpy.spin(node)
    rclpy.shutdown()

# if we want to run the script from terminal directly
#if __name__ == '__main__':
#    main()