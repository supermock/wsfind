# WSFind

Search the nearby wifi networks and send a message in Slack with the list of SSIDs not found.

## How to use?

1. Build the project:

    > **Note:** Before starting construction, in the `dependencies.txt` file there are the necessary libs.

    ```sh
    $ git clone https://github.com/supermock/wsfind.git
    $ cd wsfind
    $ make
    ```

2. Create a configuration file called `wsfind-config.json` where **wsfind** will run and with the following structure:

    ```json
    {
      "slack_token_url": "https://hooks.slack.com/services/[TOKEN]",
      "ssids": [
        "SSID1",
        "SSID2",
        "SSID3"
      ]
    }
    ```

3. Now just run the binary passing the following arguments:

    ```sh
    $ ./wsfind [interface name] [seconds between checks]
    ```

## License

MIT