#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

from example_interfaces.srv import AddTwoInts

def main(args=None):
    rclpy.init(args=args)
    node = Node("add_two_inst_no_opp")

    client = node.create_client(AddTwoInts, "add_two_ints")

    while not client.wait_for_service(1.0):
        node.get_logger().warn("Waiting for server add_two_ints...")
    # service is up

    #create request
    request = AddTwoInts.Request()
    request.a = 1
    request.b = 2
    
    # the best practice to call a service
    future = client.call_async(request)
    rclpy.spin_until_future_complete(node, future)
    #now, we have responce, we have somethink (server failed, response failed... etc)

    try: 
        responce = future.result()
        node.get_logger().info(str(responce.sum))
    except Exception as e:
        node.get_logger().error("Service call failed %r" % (e,))
    

    rclpy.shutdown()


if __name__ == "__main_":
    main()