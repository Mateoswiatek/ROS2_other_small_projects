#!/usr/bin/envpython3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import Int64

class NumberCounterNode(Node):
    def __init__(self):
        super().__init__("number_counter")
        self.subscriber_ = self.create_subscription(Int64, "number",
                                                    self.callback_number, 10)
        self.publisher_ = self.create_publisher(Int64, "number_count", 10)
        self.get_logger().info("Number Counter has been started,py")
        self.sum_ = 0


    def callback_number(self, msg):
        self.sum_ += msg.data
        new_msg = Int64()
        new_msg.data = self.sum_
        self.publisher_.publish(new_msg)


def main(args=None):
    rclpy.init(args=args)
    node = NumberCounterNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()