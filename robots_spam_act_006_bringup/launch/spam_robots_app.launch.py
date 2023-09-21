from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()

    remap_news_topic = ("robot_news", "robot_spam")

    robot_names = ["Greg", "BB8", "Spammer", "C3PO", "R2D2", "DroiD"]
    spam_nodes = []
    for name in robot_names:
        spam_nodes.append(Node(
            package="my_cpp_pkg",
            executable="robot_news_station",
            name=f"robot_new_station_{name.lower()}",
            parameters=[{"robot_name": name}],
            remappings=[
                remap_news_topic
            ]
        ))

    new_phone = Node(
        package="my_cpp_pkg",
        executable="smartphone",
        name="Useless_phone",
        remappings=[
            remap_news_topic
        ]
    )

    for node in spam_nodes:
        ld.add_action(node)

    ld.add_action(new_phone)

    return ld