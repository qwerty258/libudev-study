#include <stdio.h>
#include <libudev.h>

int main(int argc, char* argv[])
{
    struct udev* pudev = udev_new();
    if (NULL == pudev)
    {
        printf("udev_new() ERROR\n");
        return -1;
    }

    struct udev_enumerate* penumerate = udev_enumerate_new(pudev);
    udev_enumerate_add_match_subsystem(penumerate, "net");

    udev_enumerate_scan_devices(penumerate);

    struct udev_list_entry* devices = udev_enumerate_get_list_entry(penumerate);

    struct udev_list_entry* dev_list_entry = NULL;
    udev_list_entry_foreach(dev_list_entry, devices)
    {
        const char* syspath = udev_list_entry_get_name(dev_list_entry);
        if (NULL != syspath)
            printf("syspath: %s\n", syspath);

        const char* value = udev_list_entry_get_value(dev_list_entry);
        if (NULL != value)
            printf("value: %s\n", value);

        struct udev_device* dev = udev_device_new_from_syspath(pudev, syspath);

        const char* name = udev_device_get_sysname(dev);
        if (NULL != name)
            printf("name: %s\n", name);

        printf("operstate: %s\n", udev_device_get_sysattr_value(dev, "operstate"));
        printf("address: %s\n", udev_device_get_sysattr_value(dev, "address"));
        printf("\n");

        udev_device_unref(dev);
    }

    udev_enumerate_unref(penumerate);

    udev_unref(pudev);

    return 0;
}
