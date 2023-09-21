#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from functools import partial # to add more arguments to our callback, from python

from example_interfaces.srv import AddTwoInts

class AddTwoIntsClientNode(Node):
    def __init__(self):
        super().__init__("add_two_ints_client")
        self.call_add_two_ints_server(5, 8)
        self.call_add_two_ints_server(55, 43)
        self.call_add_two_ints_server(2, 1)
        self.get_logger().info("add_two_ints_client has been started")

    def call_add_two_ints_server(self, a, b): #  client, request, call server, wait for response
        #client 
        client = self.create_client(AddTwoInts, "add_two_ints")
        # w8 for server
        while not client.wait_for_service(1.0):
            self.get_logger().warn("Waiting for server add_two_ints...")
        
        # request 
        request = AddTwoInts.Request()
        request.a = a
        request.b = b

        # send request
        future = client.call_async(request)

        # response
        # np async IO library,  tutaj używamy functools (partial)
        # call the function when future is complete with partial, because we need more arguments
        future.add_done_callback(partial(self.callback_cal_add_two_ints_server, a=a, b=b))

    def callback_cal_add_two_ints_server(self, future, a, b):  # a and b, aby wiedzideć na jaki request jest response (we send parameters) 
        try:
            response = future.result()
            self.get_logger().info(str(a) + " + " + str(b) + " = " + str(response.sum))
        except Exception as e:
            self.get_logger().error("Service call failed %r" %(e,))



def main(args=None):
    rclpy.init(args=args)
    node = AddTwoIntsClientNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()