Reason Dojo 3: Fruit Ninja
---

![fruitninja](https://user-images.githubusercontent.com/4534692/46322453-d4786f00-c59d-11e8-9d0d-18bf0090c842.gif)


Reference project for our Reason Dojo 3.

### Install

```
git clone https://github.com/bsansouci/fruit-ninja.git
npm install
```

### Build
```
npm run build
```

### Start
```
npm start
```

When this fails with a 'No available audio device' error, you can run without audio with '`SDL_AUDIODRIVER="" npm start`'

To build to JS run `npm run build:web` and then run a static server, like `python -m SimpleHTTPServer` and go to `localhost:8000`. If you're using safari you can simply open the `index.html` and tick `Develop > Disable Cross-Origin Restrictions`.

To build to native run `npm run build:native` and run `npm run start:native`

The build system used is [bsb-native](https://github.com/bsansouci/bsb-native).
