package bgu.spl.net.srv.Objects;

import bgu.spl.net.srv.Command;
import bgu.spl.net.srv.CommandEncoderDecoder;

public class PrivateMessageCommand extends Command {
    private String senderName;
    private String receiveName;
    private String sendingDate;
    private String content;

    public void decodeNextByte(byte nextByte, CommandEncoderDecoder c) {
        c.decodeNextByte(nextByte,this);
    }
    public PrivateMessageCommand(int opCode) {
        super(opCode);
    }

    public String getSenderName() {
        return senderName;
    }

    public void setSenderName(String senderName) {
        this.senderName = senderName;
    }

    public String getReceiveName() {
        return receiveName;
    }

    public void setReceiveName(String receiveName) {
        this.receiveName = receiveName;
    }

    public String getSendingDate() {
        return sendingDate;
    }

    public void setSendingDate(String sendingDate) {
        this.sendingDate = sendingDate;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }
}
