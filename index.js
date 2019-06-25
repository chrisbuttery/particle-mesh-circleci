require("dotenv").config()

const express = require('express')
const bodyParser = require('body-parser')
const cors = require('cors')
const path = require('path')
const app = express()
const particle = require('particle-api-js')

const Particle = new particle()
const portNumber = 8000
let auth = null

// credentials
const deviceId = process.env.PDEVICE
const username = process.env.PUSER
const password = process.env.PPASS

// middleware
app.use(cors())
app.use(bodyParser.json())
app.use(bodyParser.urlencoded({ extended: true }))

// routes
app.post('/api/display', async (req, res, next) => {
  const { branch, user } = req.body  

  if (!auth) {
    await Particle.login({username, password})
      .then(data => {
        auth = data.body.access_token
      })
      .catch(({ status, message }) => 
        res.status(status).send({ error: message })
      )
  }

  const message = `Broken Build! ${branch} | ${user}`
  await Particle.callFunction({
    deviceId,
    name: 'display_broken_build',
    argument: message,
    auth
  })
  .then((data) => res.send(message))
  .catch((err) => {
    console.error(err)
    res.send(`callFunction error: ${JSON.stringify(err)}`)
  })

  next()
})

// error handling
app.use((err, req, res, next) => 
  res.status(422).send({ error: err.message })
)
// Go!
app.listen(portNumber, () => console.log(`Listening on port ${portNumber}`))
