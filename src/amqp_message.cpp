#include "amqp_message.h"
#include "amqp_message_p.h"

using namespace QAMQP;
MessagePrivate::MessagePrivate()
    : deliveryTag(0),
      leftSize(0)
{
}

//////////////////////////////////////////////////////////////////////////

Message::Message()
    : d(new MessagePrivate)
{
}

Message::Message(const Message &other)
    : d(other.d)
{
}

Message::~Message()
{
}

Message &Message::operator=(const Message &other)
{
    d = other.d;
    return *this;
}

bool Message::isValid() const
{
    return d->deliveryTag != 0 &&
           !d->exchangeName.isNull() &&
           !d->routingKey.isNull();
}

qlonglong Message::deliveryTag() const
{
    return d->deliveryTag;
}

bool Message::redelivered() const
{
    return d->redelivered;
}

QString Message::exchangeName() const
{
    return d->exchangeName;
}

QString Message::routingKey() const
{
    return d->routingKey;
}

QByteArray Message::payload() const
{
    return d->payload;
}

Frame::TableField Message::headers() const
{
    return d->headers;
}

bool Message::hasProperty(Property property) const
{
    return d->properties.contains(property);
}

void Message::setProperty(Property property, const QVariant &value)
{
    d->properties.insert(property, value);
}

QVariant Message::property(Property property, const QVariant &defaultValue) const
{
    return d->properties.value(property, defaultValue);
}
